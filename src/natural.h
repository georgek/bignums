/* Fast functions for natural numbers
 *
 * These functions don't do any memory management (in particular, the result
 * bignum must have enough room for the result), they ignore signs (everything
 * is positive), the length of the left operand must be greater than or equal
 * to the right operand and, for subtraction and division, the magnitude of
 * the left operand must be greater than the right. */

#ifndef H_NATURAL
#define H_NATURAL

#include "bignum.h"

void bignum_nadd(BigNum *res, BigNum *left, BigNum *right);
void bignum_nadd2(BigNum *res, BigNum *left, SHORT_INT_T right);

void bignum_nsub(BigNum *res, BigNum *left, BigNum *right);
void bignum_nsub2(BigNum *res, BigNum *left, SHORT_INT_T right);

void bignum_nmul(BigNum *res, BigNum *left, BigNum *right);
void bignum_nmul2(BigNum *res, BigNum *left, SHORT_INT_T right);

void bignum_ndiv(BigNum *q, BigNum *r, BigNum *left, BigNum *right);
void bignum_ndiv2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right);

/* three way compare (assumes same length) */
int bignum_ncmp(BigNum left, BigNum right);

#endif /* H_NATURAL */
