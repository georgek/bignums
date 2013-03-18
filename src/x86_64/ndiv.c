/* natural number division */
/* x86_64 version */

#include <stdlib.h>

#include "../bignum.h"
#include "../natural.h"

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
               & (-(signed long)s >> (WORD_LENGTH-1));
     }

     free(leftn);
     free(rightn);
}
