/* Integer multiplication. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_mul(BigNum *res, BigNum *left, BigNum *right)
{
     BigNum nr;
     unsigned reslen = left->length + right->length;

     bignum_alloc_zero(&nr, reslen);
     
     bignum_nmul(&nr, left, right);
     
     bignum_free(res);
     res->length = nr.length;
     res->max_length = nr.max_length;
     res->digits = nr.digits;
}
