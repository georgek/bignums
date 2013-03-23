# natural number addition
# x86_64 version

# void bignum_nadd(SHORT_INT_T *res,
#                  SHORT_INT_T *left, unsigned sleft,
#                  SHORT_INT_T *right, unsigned sright);

# rdi = *res
# rsi = *left
# rdx = sleft
# rcx = *right
# r8 = sright

              .Global bignum_nadd
              .Type bignum_nadd,@function
bignum_nadd:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer

              leaq  (%rdi,%r8,8), %rdi # res <- res + sright
              leaq  (%rsi,%r8,8), %rsi # left <- left + sright
              leaq  (%rcx,%r8,8), %rcx # right <- right + sright
              movq  %r8, %r11
              negq  %r11            # r11 <- -sright
              clc

nadd_main:
              movq  (%rsi,%r11,8), %rax
              adcq  (%rcx,%r11,8), %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11
              
              jnz   nadd_main

nadd_rest_set:
              pushfq                # push flags
              movq  %rdx, %rax
              subq  %r8, %rax       # rax <- sleft - sright
              jz    nadd_last_set
              leaq  (%rdi,%rax,8), %rdi # res <- res + sleft-sright
              leaq  (%rsi,%rax,8), %rsi # left <- left + sleft-sright
              movq  %rax, %r11
              negq  %r11            # r11 <- -(sleft - sright)
                                    # now r11 can be incremented sleft-sright
                                    # times before it is zero
              popfq
              
nadd_rest:
              movq  (%rsi,%r11,8), %rax
              adcq  $0, %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11
              
              jnz   nadd_rest

              jmp   nadd_last
nadd_last_set:
              popfq
nadd_last:
              movq  $0, %rax
              adcq  $0, %rax

nadd_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there

