/* natural number subtraction (might be merged with addition) */
/* Generic version */

#include "../natural.h"

/* left >= right */
void bignum_nsub(SHORT_INT_T *res,
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
}

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

