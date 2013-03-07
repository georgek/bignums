/* memory management stuff */

#ifndef H_MEMORY
#define H_MEMORY

void bignum_copy(BigNum *d, BigNum *s);
unsigned bignum_length(BigNum p);

/* doubles the max_length of the bignum, keeping the value */
void bignum_double_alloc(BigNum *bignum);

/* makes the max_length the length specified, keeping the value if it's
 * greater than or equal to the old one */
void bignum_realloc(BigNum *bignum, unsigned max_length);

void bignum_free(BigNum *p);

#endif /* H_MEMORY */
