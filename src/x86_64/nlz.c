/* number of leading zeros */
/* x86_64 version */

#include "../bignum.h"
#include "../natural.h"

/* portable (but slow) way to count leading zeros */
int nlz(SHORT_INT_T x)
{
     SHORT_INT_T s = ~(~0ul>>1);
     int i = 0;
     while (!(x&s) && i < WORD_LENGTH) {
          ++i;
          x = x << 1;
     }
     return i;
}
