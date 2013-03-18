/* natural number subtraction */
/* Generic version */

#include "../natural.h"

void bignum_nsub2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right)
{
     SHORT_INT_T k;
     int i;

     i=0;
     k = (left[i] < right); /* will overflow happen? */
     res[i] = left[i] - right;
     for (i=1; i < sleft; ++i) {
          res[i] = left[i] - k;
          k = (~0u == res[i]); /* overflow? */
     }
}
