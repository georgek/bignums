/* natural number division */
/* x86_64 version */

#include "../bignum.h"
#include "../natural.h"

void bignum_ndiv2(SHORT_INT_T *q, SHORT_INT_T *r,
                  SHORT_INT_T *left, unsigned m,
                  SHORT_INT_T right)
{
     int i;
     SHORT_INT_T t, k;

     k = 0;

     i = m - 1;
     t = left[i];
     q[i] = t/right;
     k = t - q[i]*right;
     for (i = i - 1; i >= 0; --i) {
          /* 2 full word / full word => full word division */
          /* dig_div(&(q->digits[i]), &k, */
          /*         k, left->digits[i], */
          /*         right); */
          asm volatile ("div %[d]"
                        : [q] "=a" (q[i]), [r] "=d" (k)
                        : [u] "d" (k), [l] "a" (left[i]),
                          [d] "Q" (right)
               );
     }
     *r = k;
}
