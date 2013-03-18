/* natural number multiplication */
/* Generic version */

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
