/* bignums
 *
 * bignums are stored as arrays of digits: first two cells are the length of
 * the array and the actual number of cells taken used by the bignum, the sign
 * of the first cell is the sign of the bignum, the rest of the cells are the
 * digits */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bignum.h"

/* internal functions */

static void _bignum_add2(BigNum *res, BigNum *left, SHORT_INT_T right);
static void _bignum_sub2(BigNum *res, BigNum *left, SHORT_INT_T right);
static void _bignum_mul2(BigNum *res, BigNum *left, SHORT_INT_T right);
static void _bignum_div2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right);

static void _bignum_double_alloc(BigNum *bignum);

/* initialisation functions */

void bignum_init(BigNum *p)
{
     p->length = 0;
     p->max_length = 0;
     p->neg = 0;
     p->digits = NULL;
}

void bignum_init_string(BigNum *bignum, char *string)
{
     int str_length = strlen(string);
     char *segbeg, *segend, t;
     SHORT_INT_T dig;

     /* set sign */
     if (*string == '-') {
          /* negative */
          bignum->neg = 1;
          /* advance one character */
          string += 1;
          str_length -= 1;
     }
     else {
          bignum->neg = 0;
     }

     /* allocate memory for bignum */
     bignum->max_length = DEF_NUM_WORDS;
     bignum->digits = malloc(sizeof(SHORT_INT_T)*DEF_NUM_WORDS);

     /* set first digit to first chunk ie. 0+dig */
     segbeg = string;
     segend = string+str_length%GRPOW10DIGS;
     t = *segend;
     *segend = '\0';
     *(bignum->digits) = strtoul(segbeg, NULL, 10);
     bignum->length = 1;

     /* multiply and add remaining chunks */
     while (segend-string < str_length) {
          if (bignum->max_length - bignum->length < 2) {
               /* double size of bignum */
               _bignum_double_alloc(bignum);
          }
          
          *segend = t;
          segbeg = segend;
          segend += GRPOW10DIGS;
          t = *segend;
          *segend = '\0';
          dig = strtoul(segbeg, NULL, 10);
          _bignum_mul2(bignum, bignum, GRPOW10);
          _bignum_add2(bignum, bignum, dig);
     }
}

void bignum_alloc_zero(BigNum *p, int length)
{
     p->length = 0;
     p->max_length = length;
     p->neg = 0;
     p->digits = malloc(sizeof(SHORT_INT_T)*length);
}

/* utility functions */

void bignum_free(BigNum *p)
{
     free(p->digits);
}

void bignum_print(BigNum p)
{
     BigNum w;
     int i,j,l,n;
     char **chunks;
     SHORT_INT_T r;

     bignum_init(&w);
     bignum_copy(&w, &p);

     /* array that will be big enough to contain all the GRPOW10 digits */
     l = (p.length*WORD_LENGTH + 1)/GRPOW10DIGSB2 + 1;
     
     chunks = calloc(l, sizeof(char*));

     i = 0;
     while (!bignum_is_zero(w)) {
          _bignum_div2(&w, &r, &w, GRPOW10);
          chunks[i] = malloc(sizeof(char)*GRPOW10DIGS+1);
          n = sprintf(chunks[i], "%u", r);
          /* pad with zeros */
          if (n < GRPOW10DIGS && !bignum_is_zero(w)) {
               for (j = GRPOW10DIGS; n >= 0; --j, --n) {
                    chunks[i][j] = chunks[i][n];
               }
               for (; j >= 0; --j) {
                    chunks[i][j] = '0';
               }
          }
          ++i;
     }
     for (i = i-1; i >= 0; --i) {
          printf("%s", chunks[i]);
     }
     printf("\n");
}

void bignum_copy(BigNum *d, BigNum *s)
{
     BigNum old_d = *d;
     int i;
     d->length = s->length;
     d->max_length = s->max_length;
     d->neg = s->neg;
     d->digits = malloc(sizeof(SHORT_INT_T)*d->max_length);
     for (i = 0; i < s->length; ++i) {
          d->digits[i] = s->digits[i];
     }
     bignum_free(&old_d);
}

int bignum_length(BigNum p)
{
     return p.length;
}

/* logocal operations */

int bignum_is_neg(BigNum p)
{
     return p.neg;
}

int bignum_is_zero(BigNum u)
{
     return 0 == u.length;
}

int bignum_is_one(BigNum u)
{
     return 1 == u.length && 1 == *(u.digits);
}

/* arithmetic */



/* internal */

static void _bignum_double_alloc(BigNum *bignum)
{
     bignum->max_length<<=1;
     printf("new length: %d\n", bignum->max_length);
     bignum->digits = realloc(bignum->digits, sizeof(SHORT_INT_T)*bignum->max_length);
}

/* these functions are unsigned and don't do any memory management (they
 * assume the result has enough space already) */
static void _bignum_add2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned long t, k;
     unsigned int i;

     i=0;
     res->digits[i] = left->digits[i] + right;
     k = (res->digits[i] < right);    /* did overflow happen? */
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] + k;
          k = (0 == res->digits[i]); /* overflow? */
     }
     if (k) {
          res->digits[i] = k;
          res->length = left->length + 1;
     }
     else {
          res->length = left->length;
     }
}

static void _bignum_sub2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned long t, k;
     unsigned int i;

     i=0;
     res->digits[i] = left->digits[i] - right;
     k = (res->digits[i] > right);    /* did overflow happen? */
     for (i=1; i < left->length; ++i) {
          res->digits[i] = left->digits[i] - k;
          k = (~0 == res->digits[i]); /* overflow? */
     }
     if (!res->digits[i-1]) {
          res->length = left->length - 1;
     }
     else {
          res->length = left->length;
     }
}

static void _bignum_mul2(BigNum *res, BigNum *left, SHORT_INT_T right)
{
     unsigned long t, k;
     unsigned int i;

     k=0;
     for (i=0; i < left->length; ++i) {
          t = left->digits[i] * right + k;
          res->digits[i] = t;   /* ie. t & 0x0000(...)FFFF(...) */
          k = t >> WORD_LENGTH;
     }
     if (k) {
          res->digits[i] = k;
          res->length = left->length + 1;
     }
     else {
          res->length = left->length;
     }
}

static void _bignum_div2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right)
{
     int k, i;
     unsigned t;

     k = 0;
     q->length = left->length;
     /* start with most significant digit, which may be zero */
     i = left->length - 1;
     t = left->digits[i];
     q->digits[i] = t/right;
     k = t - q->digits[i]*right;
     if (0 == q->digits[i]) {
          --(q->length);
     }
     for (i = i - 1; i >= 0; --i) {
          t = (k*RADIX + left->digits[i]);
          q->digits[i] = t/right;
          k = t - q->digits[i]*right;
     }
     *r = k;
}

