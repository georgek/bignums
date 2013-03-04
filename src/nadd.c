/* natural number addition */

#include "bignum.h"
#include "natural.h"

void bignum_nadd(BigNum *res, BigNum *left, BigNum *right)
{
     unsigned t, k;
     int i;

     res->neg = 0;
     res->length = left->length > right->length ? left->length : right->length;
     k = 0;
     for (i = 0; i < res->length; ++i) {
          t = left->digits[i] + right->digits[i] + k;
          res->digits[i] = t;   /* ie. t & 0xFFFF */
          k = t >> WORD_LENGTH;
     }
     if (k) {
          res->digits[i] = k;
          res->length++;
     }
}

void bignum_nadd2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned k;
     int i;

     res->neg = 0;
     i=0;
     res->digits[i] = left->digits[i] + right;
     k = (res->digits[i] < right);    /* did overflow happen? */
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] + k;
          k = (0 == res->digits[i]); /* overflow? */
     }
     if (k) {
          res->digits[i] = k;
          res->length = left->length + 1;
     }
     else {
          res->length = left->length;
     }
}
