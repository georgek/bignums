/* Fast functions for natural numbers
 *
 * These functions don't check their inputs at all and expect the following:
 * 
 * * res must have enough room for the actual result (amount depends on op),
 * 
 * * inputs must be nonzero,
 *
 * * length of the left operand must be greater than or equal to length of
 *   right
 *
 * * for subtraction and division, magnitude of left operand must be greater
 *   than the right
 *
 * Also, signs are not touched. */

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

/* full word multiplication and division */

/* does full word * full word => 2 full word multiplication */
void dig_mulandadd(SHORT_INT_T *ures, SHORT_INT_T *lres,
                   SHORT_INT_T left, SHORT_INT_T right);
void dig_mul(SHORT_INT_T *ures, SHORT_INT_T *lres,
             SHORT_INT_T left, SHORT_INT_T right);

/* does 2 full word / full word => full word division */
void dig_div(SHORT_INT_T *q, SHORT_INT_T *r,
             SHORT_INT_T uleft, unsigned lleft,
             SHORT_INT_T right);

int nlz(unsigned x);

/* three way compare (assumes same length) */
int bignum_ncmp(BigNum left, BigNum right);

#endif /* H_NATURAL */
