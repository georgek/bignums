### natural number addition
### x86_64 version

### void bignum_nadd(SHORT_INT_T *res,
###                  SHORT_INT_T *left, unsigned sleft,
###                  SHORT_INT_T *right, unsigned sright);

### rdi = *res
### rsi = *left
### rdx = sleft
### rcx = *right
### r8 = sright

        .Global bignum_nadd
        .Type   bignum_nadd,@function
bignum_nadd:
        pushq   %rbp            # push old base pointer to stack
        movq    %rsp,   %rbp    # copy stack pointer to base pointer

        xchgq   %rcx,   %r8
### rcx = sright
### r8 = *right
        subq    %rcx,   %rdx
### rdx = sleft - sright
        clc     

nadd_main:
        movq    (%rsi),         %rax
        adcq    (%r8),          %rax
        movq    %rax,           (%rdi)

        leaq    8(%rsi),        %rsi
        leaq    8(%r8),         %r8
        leaq    8(%rdi),        %rdi

        loop    nadd_main

        movq    %rdx,   %rcx
        jrcxz   nadd_last       # if sleft = sright
nadd_rest:
        movq    (%rsi), %rax
        adcq    $0,     %rax
        movq    %rax,   (%rdi)

        leaq    8(%rsi),        %rsi
        leaq    8(%rdi),        %rdi

        loop    nadd_rest

nadd_last:
        movq    $0, %rax
        adcq    $0, %rax

nadd_end:
        movq    %rbp, %rsp      # move stack pointer back
        popq    %rbp            # restore original base pointer
        ret                     # pop value from top of stack and go there
