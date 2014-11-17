/* simple parser for testing */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <setjmp.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "test.h"
#include "memory.h"

int yylex(void);

void yyerror(char *s)
{
     fprintf(stderr, "%s\n", s);
}

sigjmp_buf return_to_prompt;
char *rl_gets(int lineno);
void initialise_readline();
void finish_readline();
void flex_get_rl_input();
/* history file */
static const char* history_file = ".gk_history";
/* clock for timing */
clock_t time_bef;
int timing = 1;
void time_fun(void (*fun)(BigNum *, BigNum *, BigNum*), char* name,
              BigNum *res, BigNum *op1, BigNum *op2);

char* input_line = NULL;        /* line of input from readline */

char* truestr = "True";
char* falsestr = "False";
%}

%union {
     BigNum ival;               /* integer value */
};

%token <ival> INTEGER
%token QUIT

%left '<' '>' '='
%left '+' '-'
%left '*'
%left '/' '%'
%nonassoc UMINUS UPLUS
%left '^'

%type <ival> expression

%%

statement:      expression
                        {
                             printf("\n");
                             clock_t time_bef = clock();
                             bignum_print($1);
                             if (timing) {
                                  printf("Time taken for %s: %.2fs\n", "print",
                                         (double)(clock() - time_bef)
                                         / CLOCKS_PER_SEC);
                             }
                             printf("\n");
                             bignum_free(&$1);
                             return 0;
                        }
        |       error
                        {
                             return 2;
                        }
        |       QUIT
                        {
                             return 1;
                        }
        ;

expression:     expression '+' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_add, "add", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '-' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_sub, "sub", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '*' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_mul, "mul", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '/' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_divq, "divq", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '%' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_divr, "divr", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       '-' expression %prec UMINUS
                        {
                             bignum_negate(&$2);
                             $$ = $2;
                        }
        |       '+' expression %prec UPLUS
                        {
                             $$ = $2;
                        }
        |       expression '^' expression
                        {
                             bignum_init(&$$);
                             time_fun(&bignum_power, "power", &$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       '(' expression ')'
                        {
                             $$ = $2;
                        }
        |       expression '<' expression
                        {
                             bignum_init(&$$);
                             clock_t time_bef = clock();
                             if (bignum_lt($1,$3))
                             {
                                  printf("%s\n", truestr);
                             }
                             else {
                                  printf("%s\n", falsestr);
                             }
                             if (timing) {
                                  printf("Time taken for %s: %.2fs\n", "<",
                                         (double)(clock() - time_bef)
                                         /CLOCKS_PER_SEC);
                             }
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '>' expression
                        {
                             bignum_init(&$$);
                             clock_t time_bef = clock();
                             if (bignum_gt($1,$3))
                             {
                                  printf("%s\n", truestr);
                             }
                             else {
                                  printf("%s\n", falsestr);
                             }
                             if (timing) {
                                  printf("Time taken for %s: %.2fs\n", ">",
                                         (double)(clock() - time_bef)
                                         /CLOCKS_PER_SEC);
                             }
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '=' expression
                        {
                             bignum_init(&$$);
                             clock_t time_bef = clock();
                             if (bignum_eq($1,$3))
                             {
                                  printf("%s\n", truestr);
                             }
                             else {
                                  printf("%s\n", falsestr);
                             }
                             if (timing) {
                                  printf("Time taken for %s: %.2fs\n", "=",
                                         (double)(clock() - time_bef)
                                         /CLOCKS_PER_SEC);
                             }
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       INTEGER
                        {
                             $$ = $1;
                        }
        ;

%%

void handle_interrupt (int signum)
{
     signal(SIGINT, handle_interrupt);
     siglongjmp(return_to_prompt, 1);
}

int main (int argc, char *argv[])
{
     int parseret = 0;
     unsigned lineno = 1;

     initialise_readline();
     signal(SIGINT, handle_interrupt);

     /* limits */
     printf("These are the limits:\n"
            "UINT_MAX:  %20u : %16x\n"
            "ULONG_MAX: %20lu : %16lx\n"
            "USHRT_MAX: %20hu : %16hx\n",
            UINT_MAX, UINT_MAX,
            ULONG_MAX, ULONG_MAX,
            USHRT_MAX, USHRT_MAX);
     printf("^C to stop a command, ^D to exit.\n");
     
     /* user input prompt */
     while (1) {
          if (sigsetjmp(return_to_prompt, 1) == 1) {
               printf("\nStopped...\n");
          }
          input_line = rl_gets(lineno);
          if (input_line == NULL) {
               /* EOF entered, normal exit */
               printf("\n");
               break;
          }
          flex_get_rl_input();
          /* time_bef = clock(); */
          parseret = yyparse();
          /* printf("Time taken: %.2fs\n", (double)(clock() - time_bef)
           *                               / CLOCKS_PER_SEC); */
          if (parseret == 0) {
               /* normal input */
               ++lineno;
          }
          else if (parseret == 1) {
               /* normal exit */
               break;
          }
          else if (parseret == 2) {
               /* error, delete rest of line */
               free(input_line);
               input_line = NULL;
          }
     }
     free(input_line);
     input_line = NULL;

     finish_readline();
     return 0;
}

void time_fun(void (*fun)(BigNum *, BigNum *, BigNum*), char *name,
              BigNum *res, BigNum *op1, BigNum *op2)
{
     clock_t time_bef = clock();
     (*fun)(res, op1, op2);
     if (timing) {
          printf("Time taken for %s: %.2fs\n", name,
                 (double)(clock() - time_bef)/CLOCKS_PER_SEC);
     }
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
     /* write history to file */
     write_history(history_file);
     /* trim file */
     history_truncate_file(history_file, 400);
}
