/* natural number division */

#include "natural.h"

void bignum_ndiv(BigNum *q, BigNum *r, BigNum *left, BigNum *right)
{
     
}

void bignum_ndiv2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right)
{
     int k, i;
     unsigned t;

     q->neg = 0;
     
     k = 0;
     q->length = left->length;
     /* start with most significant digit, which may be zero */
     i = left->length - 1;
     t = left->digits[i];
     q->digits[i] = t/right;
     k = t - q->digits[i]*right;
     if (0 == q->digits[i]) {
          --(q->length);
     }
     for (i = i - 1; i >= 0; --i) {
          t = (k*RADIX + left->digits[i]);
          q->digits[i] = t/right;
          k = t - q->digits[i]*right;
     }
     *r = k;
}
