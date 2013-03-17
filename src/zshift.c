/* binary shifts */

#include "bignum.h"
#include "natural.h"
#include "integer.h"
#include "memory.h"

void bignum_lshift(BigNum *res, BigNum *p, unsigned count)
{
     unsigned new_length;
     
     if (0 == count) {
          bignum_set(res, p);
          return;
     }

     /* at this point we can't have that both w_count and b_count are zero, so
      * new_length > length */
     new_length = p->length + count/WORD_LENGTH + 1;

     if (res->max_length < new_length) {
          bignum_realloc(res, new_length);
     }

     bignum_nlshift(res->digits,
                    p->digits, p->length,
                    count);
     res->length = new_length;
     bignum_fix_length(res);
}

void bignum_rshift(BigNum *res, BigNum *p, unsigned count)
{
     if (0 == count) {
          bignum_set(res, p);
          return;
     }

     if (res->max_length < p->length) {
          bignum_realloc(res, p->length);
     }

     bignum_nrshift(res->digits,
                    p->digits, p->length,
                    count);
     res->length = p->length;
     bignum_fix_length(res);
}
