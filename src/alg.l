/* lexer for algebra input */

%option nounput
%option noinput
%option noyywrap
%option always-interactive

%{
#include <math.h>

#include "integer.h"
#include "parser.h"
%}

UINT 0|[1-9][0-9]*

%%

{UINT} {
     bignum_init_string(&yylval.ival, yytext);
     return INTEGER;
}

"exit"|"quit" {
     return QUIT;
}

<<EOF>> {
     printf("\n");
     return QUIT;
}

[-+*/^(),\n] {
     return *yytext;
}

[ \t]+ {
     ;                          /* ignore whitespace */
}

"$" {
     return 0;                  /* end of input */
}

. {
     printf("Character '%c' not allowed in expression.\n",*yytext);
}

%%

extern char *input_line;

void flex_get_rl_input()
{
     /* delete old buffer */
     yy_delete_buffer(YY_CURRENT_BUFFER);
     /* make new buffer which scans string and switch to it */
     yy_scan_string(input_line);
}
