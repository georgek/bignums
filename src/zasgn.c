/* Integer assignment */

#include <stdlib.h>

#include "bignum.h"
#include "integer.h"
#include "memory.h"

void bignum_set(BigNum *p, BigNum *q)
{
     int i;
     
     if (p == q) return;

     if (p->max_length < q->length) {
          bignum_realloc(p, q->length);
     }
     p->length = q->length;
     p->neg = q->neg;
     for (i = 0; i < q->length; ++i) {
          p->digits[i] = q->digits[i];
     }
}

void bignum_set_int(BigNum *p, SHORT_INT_T q)
{
     if (q == 0) {
          p->length = 0;
     }
     else {
          p->length = 1;
          p->neg = 0;
          p->digits[0] = q;
     }
}

void bignum_set_str(BigNum *p, char *string)
{
     
}
