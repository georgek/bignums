/* natural number subtraction */
/* Generic version */

#include "../natural.h"

/* left >= right */
SHORT_INT_T bignum_nsub(SHORT_INT_T *res,
                        SHORT_INT_T *left, unsigned sleft,
                        SHORT_INT_T *right, unsigned sright)
{
     SHORT_INT_T t, k;
     int i;

     k = 0;
     for (i = 0; i < sright; ++i) {
          t = left[i] - right[i] - k;
          k = (k ? t >= left[i] : t > left[i]);
          res[i] = t;
     }
     for (; i < sleft; ++i) {
          t = left[i] - k;
          k = (t > left[i]);
          res[i] = t;
     }
     return k;
}
