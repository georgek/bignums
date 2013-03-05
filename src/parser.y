/* simple parser for testing */

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "bignum.h"
#include "integer.h"

int yylex(void);

void yyerror(char *s)
{
     fprintf(stderr, "%s\n", s);
}

char *rl_gets(int lineno);
void initialise_readline();
void finish_readline();
void flex_get_rl_input();
/* history file */
static const char* history_file = ".gk_history";

char* input_line = NULL;        /* line of input from readline */
%}

%union {
     BigNum ival;               /* integer value */
};

%token <ival> INTEGER
%token QUIT

%left ','
%left '+' '-'
%left '*'
%left '/'
%nonassoc UMINUS UPLUS
%left '^'

%type <ival> expression

%%

statement:      expression
                        {
                             bignum_print($1);
                             printf("\n");
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
                             bignum_add(&$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '-' expression
                        {
                             bignum_init(&$$);
                             bignum_sub(&$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '*' expression
                        {
                             bignum_init(&$$);
                             bignum_mul(&$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       expression '/' expression
                        {
                             bignum_init(&$$);
                             bignum_divq(&$$, &$1, &$3);
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
                             bignum_power(&$$, &$1, &$3);
                             bignum_free(&$1);
                             bignum_free(&$3);
                        }
        |       '(' expression ')'
                        {
                             $$ = $2;
                        }
        |       INTEGER
                        {
                             $$ = $1;
                        }
        ;

%%

int main (int argc, char *argv[])
{
     int parseret = 0;
     unsigned lineno = 1;

     initialise_readline();

     printf("Integrator.\n"
            "Enter an expression of the form <rational function>,<var>\n"
            "to integrate <rational function> wrt <var> (x by default).\n"
            "Type quit, or enter an EOF (Ctrl-D) to quit.\n");

     /* user input prompt */
     while (1) {
          input_line = rl_gets(lineno);
          if (input_line == NULL) {
               /* EOF entered, normal exit */
               printf("\n");
               break;
          }
          flex_get_rl_input();
          parseret = yyparse();
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