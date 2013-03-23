# natural number subtraction
# x86_64 version

# void bignum_nsub2(SHORT_INT_T *res,
#                   SHORT_INT_T *left, unsigned sleft,
#                   SHORT_INT_T right)

# rdi = *res
# rsi = *left
# rdx = sleft
# rcx = right

              .Global bignum_nsub2
              .Type bignum_nsub2,@function
bignum_nsub2:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer

              leaq  (%rdi,%rdx,8), %rdi # res <- res + sleft
              leaq  (%rsi,%rdx,8), %rsi # left <- left + sleft
              movq  %rdx, %r11
              negq  %r11            # r11 <- -sleft
                                    # we now increment r11 sleft times before
                                    # it is zero

              movq  (%rsi,%r11,8), %rax
              subq  %rcx, %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11

              jz    nsub2_last  # if %r11 is now zero
nsub2_main:
              movq  (%rsi,%r11,8), %rax
              sbbq  $0, %rax
              movq  %rax, (%rdi,%r11,8)

              incq  %r11
              
              jnz   nsub2_main      # if %r11 is not zero

nsub2_last:
              movq  $0, %rax
              adcq  $0, %rax

nsub2_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
