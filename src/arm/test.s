        ;; ARM function definition
        ;; unsigned testfun(unsigned)
        .align  2               ; Align to word boundary
        .arm                    ; This is ARM code
        .global testfun
        .type   testfun STT_FUNC
testfun:
        add     r0, r0, r0
end_testfun:
        bx      lr
