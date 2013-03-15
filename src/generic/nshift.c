/* binary shifts */

#include "../bignum.h"
#include "../integer.h"

void bignum_lshift(BigNum *p, unsigned count)
{
     unsigned w_count, b_count, new_length;
     int i;

     if (0 == count) {
          return;
     }

     w_count = count / WORD_LENGTH;
     b_count = count % WORD_LENGTH;
     /* at this point we can't have that both w_count and b_count are zero, so
      * new_length > length */
     new_length = p->length + w_count + (b_count != 0);

     if (p->max_length < new_length) {
          bignum_realloc(p, new_length);
     }
     /* now array is long enough to hold shifted value, the new cells contain
      * garbage currently, we need to remove this one garbage value so that we
      * don't put garbage in the top cell */
     p->digits[p->length] = 0;
     p->length = new_length;

     for (i = p->length - 1; i > w_count; --i) {
          p->digits[i] = p->digits[i-w_count] << b_count;
          /* If b_count is zero, nothing changes here. The rhs of the & is to
           * make it work for computers that do mod WORD_LENGTH shifts */
          p->digits[i] += (p->digits[i-w_count-1] >> (WORD_LENGTH - b_count))
               & (-(signed)b_count >> WORD_LENGTH-1);
     }
     p->digits[i] = p->digits[i-w_count] << b_count;
     /* fill in zeros */
     for (i = i - 1; i >= 0; --i) {
          p->digits[i] = 0;
     }
     /* check if most sig dig is zero */
     p->length -= (p->digits[p->length - 1] ==  0);
}

void bignum_rshift(BigNum *p, unsigned count)
{
     unsigned w_count, b_count;
     int i;

     if (0 == count) {
          return;
     }

     w_count = count / WORD_LENGTH;
     b_count = count % WORD_LENGTH;

     for (i = 0; i < p->length - w_count - 1; ++i) {
          p->digits[i] = p->digits[i+w_count] >> b_count;
          p->digits[i] += (p->digits[i+w_count+1] << (WORD_LENGTH - b_count))
               & (-(signed)b_count >> WORD_LENGTH-1);
     }
     p->digits[i] = p->digits[i+w_count] >> b_count;
     /* fill in zeros */
     for (i = i + 1; i < p->length; ++i) {
          p->digits[i] = 0;
     }
     p->length = p->length - w_count;
     /* check if most sig dig is zero */
     p->length -= (p->digits[p->length - 1] ==  0);
}
