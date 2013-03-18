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
