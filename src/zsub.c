/* Integer subtraction. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_negate(BigNum *p)
{
     p->neg = !p->neg;
}

void bignum_sub(BigNum *res, BigNum *left, BigNum *right)
{
     
}
