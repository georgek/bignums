# natural number multiplication
# x86_64 version

# void bignum_nmul2(SHORT_INT_T *res,
#                   SHORT_INT_T *left, unsigned sleft,
#                   SHORT_INT_T right)

# rdi = *res
# rsi = *left
# rdx = sleft
# rcx = right

              .Global bignum_nmul2
              .Type bignum_nmul2,@function
bignum_nmul2:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer

              movq  %rdx, %r8       # we need rdx to hold mul result
# r8 = sleft
              leaq  (%rdi,%r8,8), %rdi # res <- res + sleft
              leaq  (%rsi,%r8,8), %rsi # left <- left + sleft
              movq  %r8, %r11
              negq  %r11            # r11 <- -sleft
                                    # we now increment r11 sleft times before
                                    # it is zero

              movq  $0, %r9
nmul2_main:
              movq  (%rsi,%r11,8), %rax
              mulq  %rcx            # %rdx:%rax <- %rax * right
              addq  %r9, %rax
              adcq  $0, %rdx        # %rdx:%rax <- %rdx:%rax + %r9
              movq  %rax, (%rdi,%r11,8)
              movq  %rdx, %r9

              incq  %r11

              jnz   nmul2_main

nmul2_last:
              movq  %rdx, (%rdi,%r11,8)

end_nmul2:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
