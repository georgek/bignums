/* natural number multiplication */
/* Generic version */

#include "../natural.h"

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
