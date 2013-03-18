/* binary shifts */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

void bignum_nrshift(SHORT_INT_T *res,
                    SHORT_INT_T *p, unsigned sp,
                    unsigned count)
{
     unsigned w_count, b_count;
     int i;

     w_count = count / WORD_LENGTH;
     b_count = count % WORD_LENGTH;

     for (i = 0; i < sp - w_count - 1; ++i) {
          res[i] = p[i+w_count] >> b_count;
          res[i] += (p[i+w_count+1] << (WORD_LENGTH - b_count))
               & (-(signed long)b_count >> (WORD_LENGTH-1));
     }
     res[i] = p[i+w_count] >> b_count;
     /* fill in zeros */
     for (i = i + 1; i < sp; ++i) {
          res[i] = 0;
     }
}
