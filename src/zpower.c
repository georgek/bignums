/* exponentiation */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_power(BigNum *res, BigNum *base, BigNum *exp)
{
     BigNum nres;
     SHORT_INT_T mask = ~(~0u >> 1);
     int i;

     bignum_init(&nres);
     bignum_set(&nres, base);

     i = exp->length - 1;
     /* find first on bit... */
     while (1) {
          if (exp->digits[i] & mask) break;
          mask = mask >> 1;
     }
     /* and skip over it */
     mask = mask >> 1;

     while (mask) {
          if (exp->digits[i] & mask) {
               bignum_mul(&nres, &nres, &nres);
               bignum_mul(&nres, &nres, base);
          }
          else {
               bignum_mul(&nres, &nres, &nres);
          }
          mask = mask >> 1;
     }

     for (i = i - 1; i >= 0; --i) {
          mask = ~(~0u >> 1);
          while (mask) {
               if (exp->digits[i] & mask) {
                    bignum_mul(&nres, &nres, &nres);
                    bignum_mul(&nres, &nres, base);
               }
               else {
                    bignum_mul(&nres, &nres, &nres);
               }
               mask = mask >> 1;
          }
     }

     bignum_set(res, &nres);
     bignum_free(&nres);
}
