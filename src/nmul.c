/* natural number multiplication */

#include <stdlib.h>
#include <stdio.h>

#include "natural.h"

void bignum_nmul(BigNum *res, BigNum *left, BigNum *right)
{
     BigNum *ores = NULL, nres = *res;
     int i,j;
     SHORT_INT_T t,k;

     if (res == left || res == right) {
          /* need to setup new bignum so we don't clobber left or right */
          ores = res;

          nres.length = 0;
          nres.max_length = left->length + right->length;
          nres.digits = malloc(sizeof(SHORT_INT_T)*nres.max_length);
     }

     for (i = 0; i < (left->length + right->length); ++i) {
          nres.digits[i] = 0;
     }

     for (j = 0; j < right->length; ++j) {
          k = 0;
          for (i = 0; i < left->length; ++i) {
               t = k;
               dig_mulandadd(&k, &t, left->digits[i], right->digits[j]);
               nres.digits[i+j] += t;
               k += (nres.digits[i+j] < t); /* might have overflowed */
          }
          nres.digits[j+left->length] = k;
     }

     /* find actual length of nres */
     for (i = i + j - 1; i >= 0; --i) {
          if (nres.digits[i] != 0) {
               nres.length = i + 1;
               break;
          }
     }

     *res = nres;
     bignum_free(ores);
}

void bignum_nmul2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     SHORT_INT_T t, k;
     int i;

     k=0;
     for (i=0; i < left->length; ++i) {
          t = k;
          dig_mulandadd(&k, &t, left->digits[i], right);
          res->digits[i] = t;
     }
     if (k) {
          res->digits[i] = k;
          res->length = left->length + 1;
     }
     else {
          res->length = left->length;
     }
}

/* this does (ures, lres) <- left * right + lres */
void dig_mulandadd(SHORT_INT_T *ures, SHORT_INT_T *lres,
                   SHORT_INT_T left, SHORT_INT_T right) 
{
     SHORT_INT_T masku, maskl, t, k;

     maskl = (~0u) >> WORD_LENGTH/2;
     masku = maskl << WORD_LENGTH/2;

     k = 0;
     t = (left&maskl) * (right&maskl) + (*lres&maskl);
     *lres = *lres&masku;
     *lres += t&maskl;
     k = t >> WORD_LENGTH/2;

     t = (left>>WORD_LENGTH/2) * (right&maskl) + (*lres>>WORD_LENGTH/2) + k;
     *lres = *lres&maskl;
     *lres += (t&maskl) << WORD_LENGTH/2;
     k = t >> WORD_LENGTH/2;

     *ures = k;

     k = 0;
     t = (left&maskl) * (right>>WORD_LENGTH/2) + (*lres >> WORD_LENGTH/2);
     *lres = *lres&maskl;
     *lres += t << WORD_LENGTH/2;
     k = t >> WORD_LENGTH/2;

     t = (left>>WORD_LENGTH/2) * (right>>WORD_LENGTH/2) + *ures + k;
     *ures = t&maskl;
     k = t >> WORD_LENGTH/2;
     *ures += k << WORD_LENGTH/2;
}

/* this does (ures, lres) <- left * right */
void dig_mul(SHORT_INT_T *ures, SHORT_INT_T *lres,
             SHORT_INT_T left, SHORT_INT_T right)
{
     *lres = 0;
     dig_mulandadd(ures, lres, left, right);
}
