/* binary shifts */
/* Generic version */

#include "../bignum.h"
#include "../natural.h"

void bignum_nlshift(SHORT_INT_T *res,
                    SHORT_INT_T *p, unsigned sp,
                    unsigned count)
{
     unsigned w_count, b_count;
     int i;

     w_count = count / WORD_LENGTH;
     b_count = count % WORD_LENGTH;

     /* need to make sure this cell doesn't contain garbage */
     res[sp] = 0;
     /* we always provide a result of length sp+w_count+1 so: */
     res[sp+w_count] = 0;
     sp = sp + w_count + 1;

     i = sp - 1;
     /* this will be zero if b_count = 0 */
     res[i] = (p[i-w_count-1] >> (WORD_LENGTH - b_count))
          & (-(signed long)b_count >> (WORD_LENGTH-1));
          
     for (i = i - 1; i > w_count; --i) {
          res[i] = p[i-w_count] << b_count;
          /* If b_count is zero, nothing changes here. The rhs of the & is to
           * make it work for computers that do mod WORD_LENGTH shifts */
          res[i] += (p[i-w_count-1] >> (WORD_LENGTH - b_count))
               & (-(signed long)b_count >> (WORD_LENGTH-1));
     }
     res[i] = p[i-w_count] << b_count;
     /* fill in zeros */
     for (i = i - 1; i >= 0; --i) {
          res[i] = 0;
     }
}

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
