/* natural number multiplication */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

/* this does (ures, lres) <- left * right + lres */
void dig_mulandadd(SHORT_INT_T *ures, SHORT_INT_T *lres,
                   SHORT_INT_T left, SHORT_INT_T right) 
{
     SHORT_INT_T masku, maskl, t, k;

     maskl = (~0u) >> WORD_LENGTH/2;
     masku = maskl << WORD_LENGTH/2;

     k = 0;
     t = (left&maskl) * (right&maskl) + (*lres&maskl);
     *lres = *lres&masku;
     *lres += t&maskl;
     k = t >> WORD_LENGTH/2;

     t = (left>>WORD_LENGTH/2) * (right&maskl) + (*lres>>WORD_LENGTH/2) + k;
     *lres = *lres&maskl;
     *lres += (t&maskl) << WORD_LENGTH/2;
     k = t >> WORD_LENGTH/2;

     *ures = k;

     k = 0;
     t = (left&maskl) * (right>>WORD_LENGTH/2) + (*lres >> WORD_LENGTH/2);
     *lres = *lres&maskl;
     *lres += t << WORD_LENGTH/2;
     k = t >> WORD_LENGTH/2;

     t = (left>>WORD_LENGTH/2) * (right>>WORD_LENGTH/2) + *ures + k;
     *ures = t&maskl;
     k = t >> WORD_LENGTH/2;
     *ures += k << WORD_LENGTH/2;
}
