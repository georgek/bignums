/* natural number multiplication */

#include "../natural.h"

/* this does (ures, lres) <- left * right */
void dig_mul(SHORT_INT_T *ures, SHORT_INT_T *lres,
             SHORT_INT_T left, SHORT_INT_T right)
{
     *lres = 0;
     dig_mulandadd(ures, lres, left, right);
}
