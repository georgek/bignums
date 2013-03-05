/* Integer subtraction.
 * TODO: merge this code with zadd since its virtually identical. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

#define BN_OP_zsub
#include "addorsub.h"

void bignum_negate(BigNum *p)
{
     p->neg = !p->neg;
}
