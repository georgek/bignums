#include <stdlib.h>

#include "bignum.h"
#include "memory.h"

BigNum bignum_copy(BigNum *p)
{
     BigNum q;
     int i;
     q.length = p->length;
     q.max_length = p->max_length;
     q.neg = p->neg;
     q.digits = malloc(sizeof(SHORT_INT_T)*q.max_length);
     for (i = 0; i < p->length; ++i) {
          q.digits[i] = p->digits[i];
     }
     return q;
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
