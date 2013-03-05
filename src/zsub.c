/* Integer subtraction.
 * TODO: merge this code with zadd since its virtually identical. */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

void bignum_negate(BigNum *p)
{
     p->neg = !p->neg;
}

void bignum_sub(BigNum *res, BigNum *left, BigNum *right)
{
     BigNum *t;

     /* ensure that left->length >= right->length */
     if (left->length < right->length) {
          t = left;
          left = right;
          right = t;
     }

     if (res->max_length <= left->length) {
          bignum_realloc(res, left->length+1);
     }

     if (left->neg ^ !right->neg) {
          /* different signs */
          if (left->length != right->length) {
               /* so left->length > right->length */
               bignum_nsub(res, left, right);
               res->neg = left->neg;
          }
          /* left->length == right->length */
          else if (bignum_ncmp(*left, *right) < 0) {
               /* so left < right*/
               bignum_nsub(res, right, left);
               res->neg = !right->neg;
          }
          else {
               /* so left >= right */
               bignum_nsub(res, left, right);
               res->neg = left->neg;
          }
     }
     else {
          /* same signs */
          bignum_nsub(res, left, right);
          res->neg = left->neg;
     }
}
