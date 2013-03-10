/* Integer multiplication. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_mul(BigNum *res, BigNum *left, BigNum *right)
{
     unsigned reslen = left->length + right->length;
     if (res->max_length < reslen) {
          bignum_realloc(res, left->length + right->length);
     }
     bignum_nmul(res, left, right);
     res->neg = (left->neg ^ right->neg);
}
