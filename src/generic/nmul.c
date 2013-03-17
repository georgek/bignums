/* natural number multiplication */
/* Generic version */

#include <stdlib.h>

#include "../natural.h"

void bignum_nmul(SHORT_INT_T *res,
                 SHORT_INT_T *left, unsigned sleft,
                 SHORT_INT_T *right, unsigned sright)
{
     int i,j;
     SHORT_INT_T t,k;

     for (i = 0; i < (sleft + sright); ++i) {
          res[i] = 0;
     }

     for (j = 0; j < sright; ++j) {
          k = 0;
          for (i = 0; i < sleft; ++i) {
               t = k;
               dig_mulandadd(&k, &t, left[i], right[j]);
               res[i+j] += t;
               k += (res[i+j] < t); /* might have overflowed */
          }
          res[j+sleft] = k;
     }
}

void bignum_nmul2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right)
{
     SHORT_INT_T t, k;
     int i;

     k=0;
     for (i=0; i < sleft; ++i) {
          t = k;
          dig_mulandadd(&k, &t, left[i], right);
          res[i] = t;
     }
     res[i] = k;
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
