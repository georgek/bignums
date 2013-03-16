/* natural number division */
/* x86_64 version */

#include <stdlib.h>
#include <stdio.h>

#include "../bignum.h"
#include "../natural.h"
#include "../integer.h"
#include "../memory.h"

void bignum_ndiv(SHORT_INT_T *q, SHORT_INT_T *r,
                 SHORT_INT_T *left, unsigned m,
                 SHORT_INT_T *right, unsigned n)
{
     SHORT_INT_T *leftn, *rightn; /* normalised forms */
     SHORT_INT_T qhat, rhat;      /* guesses */
     SHORT_INT_T pu, pl;
     unsigned s;
     int i,j;
     SHORT_INT_T t,t2,k,k2;

     /* Normalise by shifting right left just enough so that its high-order
      * bit is on, and shift left by the same amount. Make sure to increase
      * the length of left by 1. */

     s = nlz(right[n - 1]);
     leftn = malloc(sizeof(SHORT_INT_T)*m + 1);
     rightn = malloc(sizeof(SHORT_INT_T)*n + 1);
     bignum_nlshift(leftn, left, m, s);
     bignum_nlshift(rightn, right, n, s);

     for (j = m - n; j >= 0; --j) {
          /* compute estimate of qhat of q[j] */
          /* dig_div(&qhat, &rhat, */
          /*         leftn.digits[j+n], leftn.digits[j+n-1], */
          /*         rightn.digits[n-1]); */
          if (leftn[j+n] < rightn[n-1]) {
               asm volatile ("div %[d]"
                             : [q] "=a" (qhat), [r] "=d" (rhat)
                             : [u] "d" (leftn[j+n]),
                               [l] "a" (leftn[j+n-1]),
                               [d] "Q" (rightn[n-1])
                    );
          }
          else {
               /* qhat would overflow, which means that u_(j+n) = v_(n-1), so
                * set qhat <- b-1 and rhat <- u_(j+n-1) */
               qhat = ~0ul;
               rhat = leftn[j+n-1];
          }

     again:
          /* At this point, qhat < b; now we do the test(s) on v_(n-2). */
          dig_mul(&pu, &pl, qhat, rightn[n-2]);
          if (pu > rhat || (pu == rhat && pl > leftn[j+n-2])) {
               --qhat;
               rhat = rhat + rightn[n-1];
               if (rhat >= rightn[n-1]) {
                    /* didn't overflow */
                    goto again;
               }
          }

          /* multiply and subtract */
          k=0,k2=0;
          for (i =0; i < n; ++i) {
               t = k;
               /* (k, t)_b <- v_(i) * qhat + k*/
               dig_mulandadd(&k, &t, rightn[i], qhat);
               t2 = leftn[i+j] - t - k2;
               k2 = (k2 ? t2 >= leftn[i+j] : t2 > leftn[i+j]);
               leftn[i+j] = t2;
          }
          t2 = leftn[i+j] - k - k2;
          k2 = (k2 ? t2 >= leftn[i+j] : t2 > leftn[i+j]);
          leftn[i+j] = t2;

          q[j] = qhat;
          /* if result of mul and sub was negative we need to add back */
          if (k2) {
               q[j] = q[j] - 1;
               k = 0;
               for (i = 0; i < n; ++i) {
                    t = leftn[i+j] + rightn[i] + k;
                    k = (k ? t <= leftn[i+j] : t < leftn[i+j]);
                    leftn[i+j] = t;
               }
               leftn[i+j] = leftn[i+j] + k;
          }
     }

     /* unnormalise the remainder */
     if (r) {
          bignum_nrshift(r, leftn, n, s);
          /* leftn might be n+1 digits long even though r is definitely n */
          r[n-1] += (leftn[n] << (WORD_LENGTH - s))
               & (-(signed)s >> (WORD_LENGTH-1));
     }

     free(leftn);
     free(rightn);
}

void bignum_ndiv2(SHORT_INT_T *q, SHORT_INT_T *r,
                  SHORT_INT_T *left, unsigned m,
                  SHORT_INT_T right)
{
     int i;
     SHORT_INT_T t, k;

     k = 0;

     i = m - 1;
     t = left[i];
     q[i] = t/right;
     k = t - q[i]*right;
     for (i = i - 1; i >= 0; --i) {
          /* 2 full word / full word => full word division */
          /* dig_div(&(q->digits[i]), &k, */
          /*         k, left->digits[i], */
          /*         right); */
          asm volatile ("div %[d]"
                        : [q] "=a" (q[i]), [r] "=d" (k)
                        : [u] "d" (k), [l] "a" (left[i]),
                          [d] "Q" (right)
               );
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
             SHORT_INT_T uleft, SHORT_INT_T lleft,
             SHORT_INT_T right) {
     const SHORT_INT_T b = SRADIX; // Number base (16 bits).
     SHORT_INT_T un1, un0,          // Norm. dividend LSD's.
          vn1, vn0,              // Norm. divisor digits.
          q1, q0,                // Quotient digits.
          un32, un21, un10,      // Dividend digit pairs.
          rhat;                  // A remainder.
     long int s;                 // Shift amount for norm.

     if (uleft >= right) {      // If overflow, set rem.
          if (r != NULL) {      // to an impossible value,
               *r = ~0ul;         // and return the largest
          }
          *q = ~0ul;}             // possible quotient.

     s = nlz(right);            // 0 <= s <= 31.
     right = right << s;        // Normalize divisor.
     vn1 = right >> 16;         // Break divisor up into
     vn0 = right & 0xFFFF;      // two 16-bit digits.

     un32 = (uleft << s)
          | ((lleft >> (WORD_LENGTH - s)) & (-s >> (WORD_LENGTH-1)));
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

/* portable (but slow) way to count leading zeros */
int nlz(unsigned long x)
{
     unsigned long s = ~(~0ul>>1);
     int i = 0;
     while (!(x&s) && i < WORD_LENGTH) {
          ++i;
          x = x << 1;
     }
     return i;
}
