/* Integer addition and subtraction are almost identical functions. */

/* Ok, I basically stole this from GMP... */

#include "bignum.h"
#include "natural.h"
#include "integer.h"

#ifdef BN_OP_zadd
#define FUNCTION  bignum_add
#define VARIATION
#endif
#ifdef BN_OP_zsub
#define FUNCTION  bignum_sub
#define VARIATION !
#endif

#ifndef FUNCTION
Error, need OPERATION_add or OPERATION_sub
#endif

void FUNCTION (BigNum *res, BigNum *left, BigNum *right)
{
     BigNum *t;

     /* check for zeros */
     if (bignum_is_zero(*left)) {
          bignum_copy(res, right);
          res->neg = VARIATION res->neg;
          return;
     }
     if (bignum_is_zero(*right)) {
          bignum_copy(res, left);
          return;
     }

     /* ensure that left->length >= right->length */
     if (left->length < right->length) {
          t = left;
          left = right;
          right = t;
     }

     if (res->max_length <= left->length) {
          bignum_realloc(res, left->length+1);
     }

     if (left->neg ^ VARIATION right->neg) {
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
               res->neg = VARIATION right->neg;
          }
          else {
               /* so left >= right */
               bignum_nsub(res, left, right);
               res->neg = left->neg;
          }
     }
     else {
          /* same signs */
          bignum_nadd(res, left, right);
          res->neg = left->neg;
     }
}
