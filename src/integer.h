/* Multiple precision integers.
 *
 * These are fully memory-managed multiple-precision integers with arithmetic
 * and logic operaions.*/

#ifndef H_INTEGER
#define H_INTEGER

#include "bignum.h"

/* initialisation functions */
/* makes a new zero bignum */
void bignum_init(BigNum *p);
/* makes a new bignum from a string, returns pointer to array */
void bignum_init_string(BigNum *p, char *string);
/* make new bignum from integer */
void bignum_init_int(BigNum *p, int n);
/* makes a new bignum of a given length initialised to 0 */
void bignum_alloc_zero(BigNum *p, int length);

/* utility functions */
void bignum_print(BigNum p);

/* assignment */
void bignum_set(BigNum *p, BigNum *q);
void bignum_set_int(BigNum *p, SHORT_INT_T q);
void bignum_set_str(BigNum *p, char *string);

/* logical operations */
int bignum_is_neg(BigNum p);
int bignum_is_zero(BigNum u);
int bignum_is_one(BigNum u);

int bignum_equal(BigNum left, BigNum right);
int bignum_lt(BigNum left, BigNum right);
int bignum_gt(BigNum left, BigNum right);
int bignum_lte(BigNum left, BigNum right);
int bignum_gte(BigNum left, BigNum right);

/* arithmetic */
void bignum_negate(BigNum *p);

void bignum_add(BigNum *res, BigNum *left, BigNum *right);
void bignum_sub(BigNum *res, BigNum *left, BigNum *right);
void bignum_mul(BigNum *res, BigNum *left, BigNum *right);
void bignum_div(BigNum *q, BigNum *r, BigNum *left, BigNum *right);
void bignum_divq(BigNum *q, BigNum *left, BigNum *right);
void bignum_divr(BigNum *r, BigNum *left, BigNum *right);

void bignum_power(BigNum *res, BigNum *base, BigNum *exp);

/* greatest common divisor - binary method */
void bignum_gcd(BigNum *gcd, BigNum *u, BigNum *v);
/* greatest common divisor - Euclid's method */
void bignum_gcd2(BigNum *gcd, BigNum *u, BigNum *v);
/* least common multiple */
void bignum_lcm(BigNum *lcm, BigNum *u, BigNum *v);

#endif /* H_INTEGER */
