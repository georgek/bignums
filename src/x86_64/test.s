        # function to test linking
        .globl  testfun
        .type   testfun,@function
testfun:
        pushq   %rbp
        movq    %rsp, %rbp

        movq    %rdi, %rax
        addq    %rax, %rax

end_testfun:
        movq    %rbp, %rsp
        popq    %rbp
        ret
        