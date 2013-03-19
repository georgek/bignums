# natural number addition
# x86_64 version

# void bignum_nadd2(SHORT_INT_T *res,
#                   SHORT_INT_T *left, unsigned sleft,
#                   SHORT_INT_T right);

# rdi = *res
# rsi = *left
# rdx = sleft
# rcx = right

              .Global bignum_nadd2
              .Type bignum_nadd2,@function
bignum_nadd2:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer
              
              leaq  (%rdi,%rdx,8), %rdi # res <- res + sleft
              leaq  (%rsi,%rdx,8), %rsi # left <- left + sleft
              movq  %rdx, %r11
              negq  %r11            # r11 <- -sleft
                                    # we now increment r11 sleft times before
                                    # it is zero

              movq  (%rsi,%r11,8), %rax
              addq  %rcx, %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11

              jz    nadd2_last      # if %r11 is now zero
nadd2_main:
              movq  (%rsi,%r11,8), %rax
              adcq  $0, %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11
              
              jnz   nadd2_main      # if %r11 is not zero

nadd2_last:
              movq  $0, (%rdi,%r11,8)
              adcq  $0, (%rdi,%r11,8)

nadd2_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
