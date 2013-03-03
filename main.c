/* test code for bignums library */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "bignum.h"

char *rl_gets(int lineno);
void initialise_readline();
void finish_readline();
void flex_get_rl_input();
/* history file */
static const char* history_file = ".gk_history";

char* input_line = NULL;        /* line of input from readline */

int main(int argc, char *argv[])
{
     unsigned lineno = 1;
     int i;

     initialise_readline();

     /* limits */
     printf("These are the limits:\n"
            "UINT_MAX: %u : %x\n"
            "ULONG_MAX: %lu : %lx\n"
            "USHRT_MAX: %hu : %hx\n",
            UINT_MAX, UINT_MAX,
            ULONG_MAX, ULONG_MAX,
            USHRT_MAX, USHRT_MAX);

     BigNum tbn1, tbn2;

     /* user input prompt */
     while (1) {
          input_line = rl_gets(lineno);
          if (input_line == NULL) {
               /* EOF entered, normal exit */
               printf("\n");
               break;
          }
          printf("%s\n", input_line);
          bignum_init_string(&tbn1, input_line);
          bignum_init_int(&tbn2, -12);
          
          printf("tbn1: ");
          bignum_print(tbn1);
          printf("tbn2: ");
          bignum_print(tbn2);
          printf("equal? %d\n", bignum_equal(tbn1,tbn2));
          ++lineno;
     }
     free(input_line);
     input_line = NULL;

     finish_readline();

     return 0;
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets (int lineno)
{
     char prompt[12];

     /* If the buffer has already been allocated, return the memory to the
        free pool. */
     if (input_line) {
          free(input_line);
          input_line = NULL;
     }

     /* Get a line from the user. */
     sprintf(prompt, "(%d) -> ", lineno);
     input_line = readline(prompt);

     /* If the line has any text in it, save it on the history. */
     if (input_line && *input_line) {
          /* if this line was from history, remove the old one, unless it was
           * edited */
          if (current_history() != NULL &&
              strcmp(input_line,current_history()->line) == 0) {
               free_history_entry(remove_history(where_history()));
          }
          add_history(input_line);
          /* save history here as well in case program segfaults */
          write_history(history_file);
     }

     return input_line;
}

void initialise_readline()
{
     /* make tab just insert a tab */
     rl_bind_key ('\t', rl_insert);

     /* history stuff */
     using_history();
     /* read from file */
     read_history(history_file);
}

void finish_readline()
{
     int n;
     /* write history to file */
     n = write_history(history_file);
     /* trim file */
     history_truncate_file(history_file, 400);
}
