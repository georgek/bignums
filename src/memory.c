#include <stdlib.h>

#include "bignum.h"
#include "memory.h"

void bignum_copy(BigNum *d, BigNum *s)
{
     int i;
     d->length = s->length;
     d->max_length = s->max_length;
     d->neg = s->neg;
     d->digits = malloc(sizeof(SHORT_INT_T)*d->max_length);
     for (i = 0; i < s->length; ++i) {
          d->digits[i] = s->digits[i];
     }
}

unsigned bignum_length(BigNum p)
{
     return p.length;
}

void bignum_double_alloc(BigNum *bignum)
{
     bignum->max_length<<=1;
     bignum->digits = realloc(bignum->digits, sizeof(SHORT_INT_T)*bignum->max_length);
}

void bignum_realloc(BigNum *bignum, unsigned max_length)
{
     bignum->max_length = max_length;
     bignum->digits = realloc(bignum->digits, sizeof(SHORT_INT_T)*bignum->max_length);
}

void bignum_free(BigNum *p)
{
     if (p) {
          free(p->digits);
     }
}
