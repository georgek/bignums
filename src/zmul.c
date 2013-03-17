/* Integer multiplication. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "memory.h"

void bignum_mul(BigNum *res, BigNum *left, BigNum *right)
{
     BigNum nr;
     unsigned reslen = left->length + right->length;

     bignum_alloc_zero(&nr, reslen);
     nr.neg = left->neg ^ right->neg;
     
     bignum_nmul(nr.digits,
                 left->digits, left->length,
                 right->digits, right->length);
     nr.length = reslen;
     bignum_fix_length(&nr);
     
     bignum_free(res);
     *res = bignum_shallow_copy(&nr);
}
