/* Integer multiplication. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_mul(BigNum *res, BigNum *left, BigNum *right)
{
     bignum_realloc(res, left->length + right->length);
     bignum_nmul(res, left, right);
     res->neg = (left->neg ^ right->neg);
}
