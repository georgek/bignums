/* natural number addition */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

SHORT_INT_T bignum_nadd2(SHORT_INT_T *res,
                         SHORT_INT_T *left, unsigned sleft,
                         SHORT_INT_T right)
{
     SHORT_INT_T k;
     int i;

     i=0;
     res[i] = left[i] + right;
     k = (res[i] < right);    /* did overflow happen? */
     for (i=1; i < sleft; ++i) {
          res[i] = left[i] + k;
          k = (res[i] < k);     /* overflow? */
     }
     return k;
}
