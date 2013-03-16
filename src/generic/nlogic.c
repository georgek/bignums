/* Logic for natural numbers. */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

int bignum_ncmp(BigNum left, BigNum right)
{
     int i, cmp;

     cmp = 0;
     for (i = left.length - 1; !cmp && i >= 0; --i) {
          cmp = (left.digits[i] > right.digits[i])
               - (left.digits[i] < right.digits[i]);
     }
     return cmp;
}

