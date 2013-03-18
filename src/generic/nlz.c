/* number of leading zeros */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

/* portable (but slow) way to count leading zeros */
int nlz(SHORT_INT_T x)
{
     SHORT_INT_T s = ~(~0u>>1);
     int i = 0;
     while (!(x&s) && i < WORD_LENGTH) {
          ++i;
          x = x << 1;
     }
     return i;
}
