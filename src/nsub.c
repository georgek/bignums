/* natural number subtraction (might be merged with addition) */

#include "natural.h"

/* left >= right */

void bignum_nsub(BigNum *res, BigNum *left, BigNum *right)
{
     unsigned t, k, res_length;
     int i;

     k = 0;
     res_length = 0;
     for (i = 0; i < right->length; ++i) {
          t = left->digits[i] - right->digits[i] - k;
          res->digits[i] = t;
          k = (~(~0u>>1) & t) != 0;
          if (res->digits[i] != 0) {
               res_length = i + 1;
          }
     }
     for (; i < left->length; ++i) {
          t = left->digits[i] - k;
          res->digits[i] = t;
          k = (~(~0u>>1) & t) != 0;
          if (res->digits[i] != 0) {
               res_length = i + 1;
          }
     }
     res->length = res_length;
}

void bignum_nsub2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned k;
     int i;

     i=0;
     k = (left->digits[i] < right); /* will overflow happen? */
     res->digits[i] = left->digits[i] - right;
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] - k;
          k = (RADIX-1 == res->digits[i]);
     }
     if (!res->digits[i-1]) {
          res->length = left->length - 1;
     }
     else {
          res->length = left->length;
     }
}

