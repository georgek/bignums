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

              xorq  %r11, %r11

              movq  (%rsi), %rax
              addq  %rcx, %rax
              pushfq
              movq  %rax, (%rdi)
              incq  %r11

nadd2_main:
              cmpq  %rdx, %r11       # while i < sleft
              jge   nadd2_last

              movq  (%rsi,%r11,8), %rax
              popfq
              adcq  $0, %rax
              pushfq
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd2_main

nadd2_last:
              xorq  %rax, %rax
              popfq
              adcq  $0, %rax
              movq  %rax, (%rdi,%r11,8)

nadd2_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
