### natural number addition
### x86_64 version

### void bignum_nadd2(SHORT_INT_T *res,
###                   SHORT_INT_T *left, unsigned sleft,
###                   SHORT_INT_T right);

### rdi = *res
### rsi = *left
### rdx = sleft
### rcx = right

              .Global   bignum_nadd2
              .Type     bignum_nadd2,@function
bignum_nadd2:
        pushq   %rbp            # push old base pointer to stack
        movq    %rsp,   %rbp    # copy stack pointer to base pointer

        xchgq   %rcx,   %rdx
### rcx = sleft
### rdx = right

        movq    (%rsi), %rax
        addq    %rdx,   %rax
        movq    %rax,   (%rdi)
        loop    nadd2_main
        jmp     nadd2_last

nadd2_main:
        leaq    8(%rsi),        %rsi
        leaq    8(%rdi),        %rdi
        movq    (%rsi),         %rax
        adcq    $0,             %rax
        movq    %rax,           (%rdi)

        loop    nadd2_main

nadd2_last:
        movq    $0,     %rax
        adcq    $0,     %rax

nadd2_end:
        movq    %rbp,   %rsp    # move stack pointer back
        popq    %rbp            # restore original base pointer
        ret                     # pop value from top of stack and go there
