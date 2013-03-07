/* natural number division */

#include <stdlib.h>

#include "natural.h"

void bignum_ndiv(BigNum *q, BigNum *r, BigNum *left, BigNum *right)
{
     
}

void bignum_ndiv2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right)
{
     int i;
     SHORT_INT_T t, k;

     k = 0;
     q->length = left->length;
     /* start with most significant digit, which may become zero */
     i = left->length - 1;
     t = left->digits[i];
     q->digits[i] = t/right;
     k = t - q->digits[i]*right;
     if (0 == q->digits[i]) {
          --(q->length);
     }
     for (i = i - 1; i >= 0; --i) {
          /* 2 full word / full word => full word division */
          dig_div(&(q->digits[i]), &k,
                  k, left->digits[i],
                  right);
     }
     *r = k;
}

/* portable (but slow) way to count leading zeros (doesn't matter as it's used
 * only once in div below) */
int nlz(unsigned x)
{
     unsigned s = ~(~0u>>1);
     int i = 0;
     while (!(x&s) && i < WORD_LENGTH) {
          ++i;
          x = x << 1;
     }
     return i;
}

/* From Hacker's Delight */

/* Long division, unsigned (64/32 ==> 32).
   This procedure performs unsigned "long division" i.e., division of a
64-bit unsigned dividend by a 32-bit unsigned divisor, producing a
32-bit quotient.  In the overflow cases (divide by 0, or quotient
exceeds 32 bits), it returns a remainder of 0xFFFFFFFF (an impossible
value).
   The dividend is u1 and u0, with u1 being the most significant word.
The divisor is parameter v. The value returned is the quotient.
   Max line length is 57, to fit in hacker.book. */
void dig_div(SHORT_INT_T *q, SHORT_INT_T *r,
             SHORT_INT_T uleft, unsigned lleft,
             SHORT_INT_T right) {
     const unsigned b = SRADIX; // Number base (16 bits).
     unsigned un1, un0,          // Norm. dividend LSD's.
          vn1, vn0,              // Norm. divisor digits.
          q1, q0,                // Quotient digits.
          un32, un21, un10,      // Dividend digit pairs.
          rhat;                  // A remainder.
     int s;                      // Shift amount for norm.

     if (uleft >= right) {      // If overflow, set rem.
          if (r != NULL) {      // to an impossible value,
               *r = ~0;         // and return the largest
          }
          *q = ~0;}             // possible quotient.

     s = nlz(right);            // 0 <= s <= 31.
     right = right << s;        // Normalize divisor.
     vn1 = right >> 16;         // Break divisor up into
     vn0 = right & 0xFFFF;      // two 16-bit digits.

     un32 = (uleft << s) | (lleft >> 32 - s) & (-s >> 31);
     un10 = lleft << s;         // Shift dividend left.

     un1 = un10 >> 16;          // Break right half of
     un0 = un10 & 0xFFFF;       // dividend into two digits.

     q1 = un32/vn1;             // Compute the first
     rhat = un32 - q1*vn1;      // quotient digit, q1.
again1:
     if (q1 >= b || q1*vn0 > b*rhat + un1) {
          q1 = q1 - 1;
          rhat = rhat + vn1;
          if (rhat < b) goto again1;}

     un21 = un32*b + un1 - q1*right; // Multiply and subtract.

     q0 = un21/vn1;             // Compute the second
     rhat = un21 - q0*vn1;      // quotient digit, q0.
again2:
     if (q0 >= b || q0*vn0 > b*rhat + un0) {
          q0 = q0 - 1;
          rhat = rhat + vn1;
          if (rhat < b) goto again2;}

     if (r != NULL)                            // If remainder is wanted,
          *r = (un21*b + un0 - q0*right) >> s; // return it.
     *q = q1*b + q0;
}
