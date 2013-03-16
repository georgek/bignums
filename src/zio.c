/* Input/output functions for integers. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "memory.h"

void bignum_print(BigNum p)
{
     BigNum w;
     int i,j,l;
     char *str;
     SHORT_INT_T r, qr;

     if (bignum_is_zero(p)) {
          printf("0\n");
          return;
     }

     w = bignum_copy(&p);

     /* array that will be big enough to contain all the GRPOW10 digits
      *
      * since:
      *
      * Let n be the bignum, W_10 = GRPOW10.
      * GRPOW10DIGSB2 = fl(log_2(W_10 - 1)) + 1 <= fl(log_2(W_10)) + 1.
      * Number of bits: fl(log_2(n)) + 1 <= p.length * WORD_SIZE
      * Number of chunks required: fl(log_(W_10)(n)) + 1
      *
      * log_(W_10)(n) = (log_2(n))/(log_2(W_10))
      *              <= (p.length*WORD_SIZE+1)/(log_2(W_10))
      *              <= (p.length*WORD_SIZE+1)/(GRPOW10DIGSB2 - 1)
      *
      * So:
      * */
     l = (p.length*WORD_LENGTH + 1)/(GRPOW10DIGSB2 - 1) + 1;

     /* one long string */
     str = malloc(sizeof(char*) * GRPOW10DIGS * l + 1);

     i = GRPOW10DIGS * l;
     str[i] = '\0';

     i = i-1;
     while (!bignum_is_zero(w)) {
          bignum_ndiv2(&w, &r, &w, GRPOW10);

          for (j = 0; j < GRPOW10DIGS; ++j, --i) {
               qr = r/10;
               str[i] = '0' + (char)(r - qr*10);
               r = qr;
          }
     }
     
     if (bignum_is_neg(p)) {
          printf("-");
     }
     /* skip over leading zeros */
     for (i = i+1; '0' == str[i]; ++i);
     puts(str+i);

     bignum_free(&w);
     free(str);
}

