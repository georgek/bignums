/* natural number addition */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

SHORT_INT_T bignum_nadd(SHORT_INT_T *res,
                        SHORT_INT_T *left, unsigned sleft,
                        SHORT_INT_T *right, unsigned sright)
{
     SHORT_INT_T t, k;
     int i;

     k = 0;
     for (i = 0; i < sright; ++i) {
          t = left[i] + right[i] + k;
          k = (k ? t <= left[i] : t < left[i]);
          res[i] = t;   /* ie. t & 0xFFFF */
     }
     for (; i < sleft; ++i) {
          res[i] = left[i] + k;
          k = (res[i] < k);     /* overflow? */
     }
     return k;
}
