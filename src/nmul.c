/* natural number multiplication */

#include "natural.h"

void bignum_nmul(BigNum *res, BigNum *left, BigNum *right)
{
     
}

void bignum_nmul2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned t, k;
     int i;

     res->neg = 0;
     k=0;
     for (i=0; i < left->length; ++i) {
          t = left->digits[i] * right + k;
          res->digits[i] = t;   /* ie. t & 0x0000(...)FFFF(...) */
          k = t >> WORD_LENGTH;
     }
     if (k) {
          res->digits[i] = k;
          res->length = left->length + 1;
     }
     else {
          res->length = left->length;
     }
}
