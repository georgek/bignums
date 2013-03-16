@ ARM function definition
@ unsigned testfun(unsigned)
@ ARM version
              .Align 2              @ Align to word boundary
              .Arm                  @ This is ARM code
              .Global testfun
              .Type testfun STT_FUNC
testfun:
              add   r0, r0, r0      @ double arg and return it
end_testfun:
              bx    lr              @ return
