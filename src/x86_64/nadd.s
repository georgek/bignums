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

              movq  (%rsi), %rax
              addq  (%rcx), %rax
              movq  %rax, (%rdi)

              movq  $1, %r11        # i <- 1

nadd_main:
              cmpq  %r8, %r11       # while i < sright
              jge   nadd_rest

              movq  (%rsi,%r11,8), %rax
              adcq  (%rcx,%r11,8), %rax
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd_main

nadd_rest:
              cmpq  %rdx, %r11      # while i <= sleft
              jg    nadd_end

              movq  (%rsi,%r11,8), %rax
              adcq  $0, %rax        # just adding on the carry
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd_rest

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

              movq  (%rsi), %rax
              addq  %rcx, %rax
              movq  %rax, (%rdi)

              movq  $1, %r11        # i <- 1

nadd2_main:
              cmpq  %r8, %r11       # while i < slength
              jge   nadd2_end

              movq  (%rsi,%r11,8), %rax
              adcq  $0, %rax
              movq  %rax, (%rdi,%r11,8)
              incq  %r11
              jmp   nadd2_main

nadd2_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
