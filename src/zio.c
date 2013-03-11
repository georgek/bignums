/* Input/output functions for integers. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bignum.h"
#include "integer.h"
#include "memory.h"

void bignum_print(BigNum p)
{
     BigNum w;
     int i,j,l,n;
     char **chunks;
     SHORT_INT_T r;

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
     
     chunks = calloc(l, sizeof(char*));

     i = 0;
     while (!bignum_is_zero(w)) {
          bignum_ndiv2(&w, &r, &w, GRPOW10);
          chunks[i] = malloc(sizeof(char)*GRPOW10DIGS+1);
          n = sprintf(chunks[i], "%u", r);
          /* pad with zeros */
          if (n < GRPOW10DIGS && !bignum_is_zero(w)) {
               for (j = GRPOW10DIGS; n >= 0; --j, --n) {
                    chunks[i][j] = chunks[i][n];
               }
               for (; j >= 0; --j) {
                    chunks[i][j] = '0';
               }
          }
          ++i;
     }
     
     if (bignum_is_neg(p)) {
          printf("-");
     }
     for (i = i-1; i >= 0; --i) {
          printf("%s", chunks[i]);
          free(chunks[i]);
     }
     printf("\n");

     bignum_free(&w);
     free(chunks);
}

