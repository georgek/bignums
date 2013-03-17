/* natural number multiplication */

#include <stdlib.h>

#include "../natural.h"

void bignum_nmul(SHORT_INT_T *res,
                 SHORT_INT_T *left, unsigned sleft,
                 SHORT_INT_T *right, unsigned sright)
{
     int i,j;
     SHORT_INT_T t,k;

     for (i = 0; i < (sleft + sright); ++i) {
          res[i] = 0;
     }

     for (j = 0; j < sright; ++j) {
          k = 0;
          for (i = 0; i < sleft; ++i) {
               t = k;
               dig_mulandadd(&k, &t, left[i], right[j]);
               res[i+j] += t;
               k += (res[i+j] < t); /* might have overflowed */
          }
          res[j+sleft] = k;
     }
}

void bignum_nmul2(SHORT_INT_T *res,
                  SHORT_INT_T *left, unsigned sleft,
                  SHORT_INT_T right)
{
     SHORT_INT_T t, k;
     int i;

     k=0;
     for (i=0; i < sleft; ++i) {
          t = k;
          dig_mulandadd(&k, &t, left[i], right);
          res[i] = t;
     }
     res[i] = k;
}

/* this does (ures, lres) <- left * right + lres */
void dig_mulandadd(SHORT_INT_T *ures, SHORT_INT_T *lres,
                   SHORT_INT_T left, SHORT_INT_T right) 
{
     SHORT_INT_T t = *lres;
     /* asm volatile ("mul %[r];" */
     /*               "add %[k], %%eax;" */
     /*               "adc %[z], %%edx;" */
     /*               : "=d" (*ures), "=a" (*lres) */
     /*               : [l] "a" (left), [r] "r" (right), [k] "r" (t), [z] "i" (0) */
     /*      ); */
     asm ("mul %[r];"
          : "=d" (*ures), "=a" (*lres)
          : [l] "a" (left), [r] "Q" (right)
          );
     asm volatile ("add %[k], %[l];"
          "adc %[z], %[u];"
          : "=d" (*ures), "=a" (*lres)
          : [u] "d" (*ures), [l] "a" (*lres), [k] "Q" (t), [z] "i" (0)
          );
     /* *lres = *lres + t; */
     /* *ures = *ures + (*lres < t); */
}

/* this does (ures, lres) <- left * right */
void dig_mul(SHORT_INT_T *ures, SHORT_INT_T *lres,
             SHORT_INT_T left, SHORT_INT_T right)
{
     *lres = 0;
     dig_mulandadd(ures, lres, left, right);
}
