/* Initialisation functions for integers. */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bignum.h"
#include "integer.h"

void bignum_init(BigNum *p)
{
     p->length = 0;
     p->max_length = 0;
     p->neg = 0;
     p->digits = NULL;
}

void bignum_init_string(BigNum *bignum, char *string)
{
     int str_length;
     char *segbeg, *segend, t;
     SHORT_INT_T dig;
     
     /* set sign */
     if (*string == '-') {
          /* negative */
          bignum->neg = 1;
          /* advance one character */
          string += 1;
     }
     else {
          bignum->neg = 0;
     }
     /* skip over leading zeros */
     while (*string == '0') {
          string += 1;
     }
     if (*string == '\0') {
          bignum->length = 0;
          bignum->max_length = 0;
          bignum->digits = NULL;
          return;
     }

     str_length = strlen(string);

     /* allocate memory for bignum */
     bignum->max_length = DEF_NUM_WORDS;
     bignum->digits = malloc(sizeof(SHORT_INT_T)*DEF_NUM_WORDS);

     /* set first digit to first chunk ie. 0+dig */
     segbeg = string;
     segend = string+str_length%GRPOW10DIGS;
     t = *segend;
     *segend = '\0';
     *(bignum->digits) = strtoul(segbeg, NULL, 10);

     bignum->length = 1;

     /* multiply and add remaining chunks */
     while (segend-string < str_length) {
          if (bignum->max_length - bignum->length < 2) {
               /* double size of bignum */
               bignum_double_alloc(bignum);
          }
          
          *segend = t;
          segbeg = segend;
          segend += GRPOW10DIGS;
          t = *segend;
          *segend = '\0';
          dig = strtoul(segbeg, NULL, 10);
          bignum_nmul2(bignum, bignum, GRPOW10);
          bignum_nadd2(bignum, bignum, dig);
     }
}

void bignum_init_int(BigNum *p, int n)
{
     unsigned y;
     p->length = n != 0;
     p->max_length = DEF_NUM_WORDS;
     p->neg = n < 0;
     p->digits = malloc(sizeof(SHORT_INT_T)*p->max_length);
     y = ~(~0u>>1) & n ? ~0 : 0; /* ie. y = n >> word_length (signed) */
     p->digits[0] = (n ^ y) - y; /* absolute value of n */
}

void bignum_alloc_zero(BigNum *p, int length)
{
     p->length = 0;
     p->max_length = length;
     p->neg = 0;
     p->digits = malloc(sizeof(SHORT_INT_T)*length);
}

void bignum_free(BigNum *p)
{
     free(p->digits);
}
