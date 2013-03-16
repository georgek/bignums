/* natural number subtraction (might be merged with addition) */
/* Generic version */

#include "../natural.h"

/* left >= right */

void bignum_nsub(BigNum *res, BigNum *left, BigNum *right)
{
     SHORT_INT_T t, k;
     unsigned res_length;
     int i;

     k = 0;
     res_length = 0;
     for (i = 0; i < right->length; ++i) {
          t = left->digits[i] - right->digits[i] - k;
          k = (k ? t >= left->digits[i] : t > left->digits[i]);
          res->digits[i] = t;
          
          if (res->digits[i]) {
               ++res_length;
          }
     }
     for (; i < left->length; ++i) {
          t = left->digits[i] - k;
          k = (t > left->digits[i]);
          res->digits[i] = t;
          if (res->digits[i]) {
               ++res_length;
          }
     }
     res->length = res_length;
}

void bignum_nsub2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     SHORT_INT_T k;
     int i;

     i=0;
     k = (left->digits[i] < right); /* will overflow happen? */
     res->digits[i] = left->digits[i] - right;
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] - k;
          k = (~0u == res->digits[i]); /* overflow? */
     }
     /* reduce length if most significant digit is zero */
     res->length = left->length - (0 == res->digits[i-1]);
}

