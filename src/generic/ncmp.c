/* Three way compare. */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

int bignum_ncmp(SHORT_INT_T *left, SHORT_INT_T *right, unsigned s)
{
     int i, cmp;

     cmp = 0;
     for (i = s - 1; !cmp && i >= 0; --i) {
          cmp = (left[i] > right[i])
               - (left[i] < right[i]);
     }
     return cmp;
}

