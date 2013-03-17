/* memory management stuff */

#ifndef H_MEMORY
#define H_MEMORY

#include "bignum.h"

/* returns copy of p with same digit array */
BigNum bignum_shallow_copy(BigNum *p);
/* returns copy of p with copied digit array */
BigNum bignum_copy(BigNum *p);

unsigned bignum_length(BigNum p);

/* sets bignum length to a value less than or equal to its current value by
 * removing leading zeros */
void bignum_fix_length(BigNum *p);

/* doubles the max_length of the bignum, keeping the value */
void bignum_double_alloc(BigNum *bignum);

/* makes the max_length the length specified, keeping the value if it's
 * greater than or equal to the old one */
void bignum_realloc(BigNum *bignum, unsigned max_length);

void bignum_free(BigNum *p);

#endif /* H_MEMORY */

/* Local Variables: */
/* mode: c */
/* End: */
