/* natural number addition */

#include "bignum.h"
#include "natural.h"

void bignum_nadd(BigNum *res, BigNum *left, BigNum *right)
{
     unsigned t, k;
     int i;

     k = 0;
     for (i = 0; i < right->length; ++i) {
          t = left->digits[i] + right->digits[i] + k;
          res->digits[i] = t;   /* ie. t & 0xFFFF */
          k = t >> WORD_LENGTH;
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
     unsigned k;
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
