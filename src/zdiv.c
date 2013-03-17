/* Integer division. */

#include <stdlib.h>
#include <stdio.h>

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "memory.h"

/* either q or r (or both) can actually be NULL */
void bignum_div(BigNum *q, BigNum *r, BigNum *left, BigNum *right)
{
     BigNum nq;
     unsigned qlen = left->length - right->length + 1;
     SHORT_INT_T sr;
     int cmp;

     /* trivial cases */
     if (left->length < right->length) {
          /* left < right */
          if (q) {
               bignum_set_int(q, 0);
          }
          if (r) {
               bignum_set(r, right);
          }
          return;
     }
     if (right->length == left->length) {
          cmp = bignum_ncmp(left->digits, right->digits, left->length);
          
          if (cmp < 0) {
               /* left < right */
               if (q) {
                    bignum_set_int(q, 0);
               }
               if (r) {
                    bignum_set(r, right);
               }
               return;
          }
          if (cmp == 0) {
               /* left == right */
               if (q) {
                    bignum_set_int(q, 1);
                    q->neg = left->neg ^ right->neg;
               }
               if (r) {
                    bignum_set_int(r, 0);
               }
               return;
          }
     }
     /* so left > right */

     bignum_alloc_zero(&nq, qlen);
     if (r && (r->max_length < right->length)) {
          bignum_realloc(r, right->length);
     }

     if (right->length == 1) {
          bignum_ndiv2(nq.digits, &sr,
                       left->digits, left->length,
                       right->digits[0]);
          nq.length = qlen;
          bignum_fix_length(&nq);
          if (q) {
               bignum_free(q);
               q->length = nq.length;
               q->max_length = nq.max_length;
               q->digits = nq.digits;
               nq.digits = NULL;
          }
          if (r) {
               bignum_set_int(r, sr);
          }
     }
     else {
          if (r) {
               bignum_ndiv(nq.digits, r->digits,
                           left->digits, left->length,
                           right->digits, right->length);
               r->length = right->length;
               bignum_fix_length(r);
          }
          else{
               bignum_ndiv(nq.digits, NULL,
                           left->digits, left->length,
                           right->digits, right->length);
          }
          nq.length = qlen;
          bignum_fix_length(&nq);
          if (q) {
               bignum_free(q);
               q->length = nq.length;
               q->max_length = nq.max_length;
               q->digits = nq.digits;
               nq.digits = NULL;
          }
     }
     if (q) {
          q->neg = (left->neg ^ right->neg);
     }
     if (r) {
          r->neg = right->neg;
     }

     bignum_free(&nq);
}

void bignum_divq(BigNum *q, BigNum *left, BigNum *right)
{
     bignum_div(q, NULL, left, right);
}

void bignum_divr(BigNum *r, BigNum *left, BigNum *right)
{
     bignum_div(NULL, r, left, right);
}
