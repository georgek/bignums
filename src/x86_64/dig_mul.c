/* natural number multiplication */

#include "../natural.h"

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
