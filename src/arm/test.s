        # function to test linking
        .globl  testfun
        .type   testfun,@function
testfun:
        add r0, r0, r0

end_testfun:
        mov     pc, lr
        