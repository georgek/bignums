/* natural number addition */

#include "bignum.h"
#include "natural.h"

void bignum_nadd(BigNum *res, BigNum *left, BigNum *right)
{
     SHORT_INT_T t, k;
     int i;

     k = 0;
     for (i = 0; i < right->length; ++i) {
          t = left->digits[i] + right->digits[i] + k;
          k = (k ? t <= left->digits[i] : t < left->digits[i]);
          res->digits[i] = t;   /* ie. t & 0xFFFF */
     }
     for (; i < left->length; ++i) {
          res->digits[i] = left->digits[i] + k;
          k = (0 == res->digits[i]); /* overflow? */
     }
     res->digits[i] = k;
     res->length = left->length + k;
}

void bignum_nadd2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     SHORT_INT_T k;
     int i;

     i=0;
     res->digits[i] = left->digits[i] + right;
     k = (res->digits[i] < right);    /* did overflow happen? */
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] + k;
          k = (0 == res->digits[i]); /* overflow? */
     }
     res->digits[i] = k;
     res->length = left->length + k;
}
