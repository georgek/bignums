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

              xorq  %r11, %r11      # i <- 0 (also clears carry)
              pushfq

nadd_main:
              cmpq  %r8, %r11       # while i < sright
              jge   nadd_rest

              movq  (%rsi,%r11,8), %rax
              popfq
              adcq  (%rcx,%r11,8), %rax
              pushfq
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd_main

nadd_rest:
              cmpq  %rdx, %r11      # while i <= sleft
              jge   nadd_last

              movq  (%rsi,%r11,8), %rax
              popfq
              adcq  $0, %rax        # just adding on the carry
              pushfq
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd_rest

nadd_last:
              xorq  %rax, %rax
              popfq
              adcq  $0, %rax
              movq  %rax, (%rdi,%r11,8)

nadd_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there

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
              
              movq  %rcx, %r11      # move right out of %rcx because we need it
# r11 = right
              movq  %rdx, %rcx      # now rcx can be decremented sleft times
                                    # before it is zero

              xorq  %r8, %r8        # use r8 to index (this also clears carry)
              
              movq  (%rsi), %rax
              addq  %r11, %rax
              movq  %rax, (%rdi)

              incq  %r8
              decq  %rcx

nadd2_main:
              jrcxz nadd2_last

              movq  (%rsi,%r8,8), %rax
              adcq  $0, %rax
              movq  %rax, (%rdi,%r8,8)

              incq  %r8
              decq  %rdx
              
              jmp   nadd2_main

nadd2_last:
              adcq  $0, (%rdi,%r8,8)

nadd2_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
