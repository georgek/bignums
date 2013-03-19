# Three way compare.
# x86_64 version

# int bignum_nadd2(SHORT_INT_T *left,
#                  SHORT_INT_T *right,
#                  unsigned s);

# rdi = *left
# rsi = *right
# rdx = s

              .Global bignum_ncmp
              .Type bignum_ncmp,@function
bignum_ncmp:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer
              
              decq  %rdx
ncmp_main:
              movq  (%rdi,%rdx,8), %rax
              cmpq  (%rsi,%rdx,8), %rax
              ja    greater
              jb    less
              decq  %rdx
              jnz   ncmp_main

              movq  (%rdi), %rax
              cmpq  (%rsi), %rax
              ja    greater
              jb    less

equal:
              movq  $0, %rax
              jmp   ncmp_end
greater:
              movq  $1, %rax
              jmp   ncmp_end

less:
              movq  $-1, %rax
              
ncmp_end:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
