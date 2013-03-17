/* Integer addition and subtraction are almost identical functions. */

/* Ok, I basically stole this from GMP... */

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "memory.h"

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
          bignum_set(res, right);
          res->neg = VARIATION res->neg;
          return;
     }
     if (bignum_is_zero(*right)) {
          bignum_set(res, left);
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
               bignum_nsub(res->digits,
                           left->digits, left->length,
                           right->digits, right->length);
               res->length = left->length;
               bignum_fix_length(res);
               res->neg = left->neg;
          }
          /* left->length == right->length */
          else if (bignum_ncmp(left->digits, right->digits,
                        left->length) < 0) {
               /* so left < right*/
               bignum_nsub(res->digits,
                           right->digits, right->length,
                           left->digits, left->length);
               res->length = right->length;
               bignum_fix_length(res);
               res->neg = VARIATION right->neg;
          }
          else {
               /* so left >= right */
               bignum_nsub(res->digits,
                           left->digits, left->length,
                           right->digits, right->length);
               res->length = left->length;
               bignum_fix_length(res);
               res->neg = left->neg;
          }
     }
     else {
         /* same signs */
         bignum_nadd(res->digits,
                     left->digits, left->length,
                     right->digits, right->length);
         res->length = left->length + 1;
         bignum_fix_length(res);
         res->neg = left->neg;
     }
}

/* Local Variables: */
/* mode: c */
/* End: */
