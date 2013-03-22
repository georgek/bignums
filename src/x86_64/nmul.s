### natural number multiplication
### x86_64 version

### void bignum_nmul(SHORT_INT_T *res,
###                  SHORT_INT_T *left, unsigned sleft,
###                  SHORT_INT_T *right, unsigned sright)

### rdi = *res
### rsi = *left
### rdx = sleft
### rcx = *right
### r8 = sright

        .Global bignum_nmul
        .Type bignum_nmul,@function
bignum_nmul:
        pushq   %rbp                 # push old base pointer to stack
        movq    %rsp,   %rbp         # copy stack pointer to base pointer
        
        pushq   %r12
        pushq   %r13
        
        movq    %rdx,   %r10         # we need rdx free        
## r10 = sleft
        leaq    (%rsi,%rdx,8),  %rsi # left <- left + sleft
        leaq    (%rcx,%r8,8),   %rcx # right <- right + sright
        
        movq    %rdx,           %rax
        addq    %r8,            %rax # sleft + sright
        jz      end_nmul
        leaq    (%rdi,%rax,8),  %rdi
        negq    %rax
        ## set result digits to all zeros
res_zero:
        movq    $0,             (%rdi,%rax,8)
        incq    %rax
        jnz     res_zero
        
        negq    %r8             # j <- 0
        ## for r8 = -sright -> 0
right_loop:
        movq    $0,     %rdx    # k <- 0

        movq    %r10,   %r11
        negq    %r11            # i <- 0

        movq    %r8,    %r12
        addq    %r11,   %r12    # i+j

        ## for r11 = -sleft -> 0
left_loop:
        movq    %rdx,           %r13 # save this
        movq    (%rsi,%r11,8),  %rax
        mulq    (%rcx,%r8,8)
        addq    %r13,           %rax
        adcq    $0,             %rdx
        addq    %rax,           (%rdi,%r12,8)
        adcq    $0,             %rdx

left_loop_next:
        incq    %r12
        incq    %r11
        jnz     left_loop

        movq    %rdx,   (%rdi,%r12,8)

right_loop_next:
        incq    %r8
        jnz     right_loop
              
end_nmul:
        popq    %r13
        popq    %r12
        movq    %rbp,   %rsp    # move stack pointer back
        popq    %rbp            # restore original base pointer
        ret                     # pop value from top of stack and go there

### Local Variables:
### asm-comment-char: 35
### End:
