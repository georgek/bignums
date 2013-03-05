/* natural number subtraction (might be merged with addition) */

#include "natural.h"

/* left >= right */

void bignum_nsub(BigNum *res, BigNum *left, BigNum *right)
{

}

void bignum_nsub2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned k;
     int i;

     i=0;
     res->digits[i] = left->digits[i] - right;
     k = (res->digits[i] > right);    /* did overflow happen? */
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] - k;
          k = (~0 == res->digits[i]); /* overflow? */
     }
     if (!res->digits[i-1]) {
          res->length = left->length - 1;
     }
     else {
          res->length = left->length;
     }
}
