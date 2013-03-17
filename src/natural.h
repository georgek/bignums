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

/* result has sleft+1 places */
void bignum_nadd(SHORT_INT_T *res,
                 SHORT_INT_T *left, unsigned sleft,
                 SHORT_INT_T *right, unsigned sright);
void bignum_nadd2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right);

/* result has sleft places */
void bignum_nsub(SHORT_INT_T *res,
                 SHORT_INT_T *left, unsigned sleft,
                 SHORT_INT_T *right, unsigned sright);
void bignum_nsub2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right);

/* there must be no overlap between res and either left or right */
/* result has sleft + sright places */
void bignum_nmul(SHORT_INT_T *res,
                 SHORT_INT_T *left, unsigned sleft,
                 SHORT_INT_T *right, unsigned sright);
void bignum_nmul2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right);
/* there must be no overlap between q and r and either left or right */
/* quotient has m - n + 1 places, remainder has n places */
void bignum_ndiv(SHORT_INT_T *q, SHORT_INT_T *r,
                 SHORT_INT_T *left, unsigned m,
                 SHORT_INT_T *right, unsigned n);
void bignum_ndiv2(SHORT_INT_T *q, SHORT_INT_T *r,
                  SHORT_INT_T *left, unsigned m,
                  SHORT_INT_T right);
/* void bignum_ndiv(BigNum *q, BigNum *r, BigNum *left, BigNum *right); */
/* void bignum_ndiv2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right); */

/* binary shifts */
/* result has sp + count/WORD_LENGTH + 1 places */
void bignum_nlshift(SHORT_INT_T *res,
                    SHORT_INT_T *p, unsigned sp,
                    unsigned count);
/* result has sp places */
void bignum_nrshift(SHORT_INT_T *res,
                    SHORT_INT_T *p, unsigned sp,
                    unsigned count);
/* void bignum_lshift(BigNum *p, unsigned count); */
/* void bignum_rshift(BigNum *p, unsigned count); */

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

/* number of leading zeros function */
int nlz(unsigned x);

/* three way compare (assumes same length) */
int bignum_ncmp(SHORT_INT_T *left, SHORT_INT_T *right, unsigned s);

#endif /* H_NATURAL */

/* Local Variables: */
/* mode: c */
/* End: */
