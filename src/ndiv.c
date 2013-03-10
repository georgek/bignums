/* natural number division */

#include <stdlib.h>
#include <stdio.h>

#include "bignum.h"
#include "natural.h"
#include "memory.h"

void bignum_ndiv(BigNum *q, BigNum *r, BigNum *left, BigNum *right)
{
     BigNum *oq = NULL, nq = *q;
     BigNum leftn, rightn;      /* normalised forms */
     SHORT_INT_T qhat, rhat;    /* guesses */
     SHORT_INT_T pu, pl;
     unsigned s, m, n;
     int i,j;
     SHORT_INT_T t,t2,k,k2;

     m = left->length;
     n = right->length;

     nq.length = m - n + 1;
     
     if (q == left || q == right) {
          /* need to setup new bignum so we don't clobber left or right */
          oq = q;
          nq.max_length = nq.length;
          nq.digits = malloc(sizeof(SHORT_INT_T)*nq.max_length);
     }

     /* Normalise by shifting right left just enough so that its high-order
      * bit is on, and shift left by the same amount. Make sure to increase
      * the length of left by 1. */

     s = nlz(right->digits[n - 1]);
     leftn = bignum_copy(left);
     rightn = bignum_copy(right);
     bignum_lshift(&leftn, s);
     bignum_lshift(&rightn, s);
     if (leftn.length == m) {
          bignum_realloc(&leftn, m+1);
     }

     for (j = nq.length - 1; j >= 0; --j) {
          /* compute estimate of qhat of q[j] */
          dig_div(&qhat, &rhat,
                  leftn.digits[j+n], leftn.digits[j+n-1],
                  rightn.digits[n-1]);
          if (qhat == ~0 && rhat == ~0) {
               /* qhat overflowed, set qhat <- b-1 (already done) and rhat <-
                * u_(j+n-1) */
               rhat = rightn.digits[n-1];
          }
     again:
          /* At this point, qhat < b; now we do the test(s) on v_(n-2). */
          dig_mul(&pu, &pl, qhat, rightn.digits[n-2]);
          if (pu > rhat || (pu == rhat && pl > leftn.digits[j+n-2])) {
               --qhat;
               rhat = rhat + rightn.digits[n-1];
               if (rhat >= rightn.digits[n-1]) {
                    /* didn't overflow */
                    goto again;
               }
          }

          /* multiply and subtract */
          k=0,k2=0;
          for (i =0; i < n; ++i) {
               t = k;
               /* (k, t)_b <- v_(i) * qhat */
               dig_mulandadd(&k, &t, rightn.digits[i], qhat);
               t2 = leftn.digits[i] - t - k2;
               k2 = (k2 ? t2 >= leftn.digits[i] : t2 > leftn.digits[i]);
               leftn.digits[i] = t2;
          }
          t2 = leftn.digits[i] - k - k2;
          k2 = (k2 ? t2 >= leftn.digits[i] : t2 > leftn.digits[i]);
          leftn.digits[i] = t2;

          nq.digits[j] = qhat;
          /* if result of mul and sub was negative we need to add back */
          if (k2) {
               nq.digits[j] = nq.digits[j] - 1;
               k = 0;
               for (i = 0; i < n; ++i) {
                    t = leftn.digits[i+j] + rightn.digits[i] + k;
                    k = (k ? t <= leftn.digits[i] : t < leftn.digits[i]);
                    leftn.digits[i+j] = t;
               }
               leftn.digits[i+j] = leftn.digits[i+j] + k;
          }
     }

     /* work out real size of nq */
     if (nq.digits[nq.length - 1] == 0) {
          nq.length--;
     }

     /* unnormalise the remainder */
     bignum_rshift(&leftn, s);
     if (r) {
          bignum_free(r);
          *r = leftn;
     }

     *q = nq;
     bignum_free(oq);
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

     un32 = (uleft << s) | (lleft >> WORD_LENGTH - s) & (-s >> (WORD_LENGTH-1));
     un10 = lleft << s;         // Shift dividend left.

     un1 = un10 >> WORD_LENGTH/2; // Break right half of
     un0 = un10 & (SRADIX-1);   // dividend into two digits.

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
