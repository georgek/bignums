# function to test linking
# unsigned testfun(unsigned)
# x86_64 version
              .Global testfun
              .Type testfun,@function
testfun:
              pushq %rbp            # push old base pointer to stack
              movq  %rsp, %rbp      # copy stack pointer to base pointer

              movq  %rdi, %rax      # copy first argument to rax
              addq  %rax, %rax      # double rax (return value)

end_testfun:
              movq  %rbp, %rsp      # move stack pointer back
              popq  %rbp            # restore original base pointer
              ret                   # pop value from top of stack and go there
