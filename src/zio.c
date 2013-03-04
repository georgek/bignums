/* Input/output functions for integers. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bignum.h"
#include "integer.h"

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

     bignum_init(&w);
     bignum_copy(&w, &p);

     /* array that will be big enough to contain all the GRPOW10 digits */
     l = (p.length*WORD_LENGTH + 1)/GRPOW10DIGSB2 + 1;
     
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
     }
     printf("\n");
}

