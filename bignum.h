/* bignums are arbitrary precision integers */
/* **TODO**: make sure this works with any system not just mine,
     probably using a configure script to work out which types to use
     and the radix */

#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include <limits.h>

/* long int type for result of multiplication */
#define LONG_INT_T unsigned int
/* and the argument type for printf */
#define PRINT_LI(var) printf("%lu", var)

/* short int type for storage */
#define SHORT_INT_T unsigned short int
/* signed version for checking sign of bignum */
#define S_SHORT_INT_T signed short int
/* and its argument for printf */
#define PRINT_SI(var) printf("%u", var)

/* find good value for radix,
 * this is good for 16 bit short int (for 32 bit system) */
#define RADIX   0x10000
#define GRPOW10   10000
#define GRPOW10DIGS 4
#define GRPOW10DIGSB2 14
/* this is good for a 16 bit short int (for 32 bit system) */
/* #define RADIX 10000 */
/* word length is the actual length of SHORT_INT_T in bits */
#define WORD_LENGTH 16

/* number of words that bignums start with */
#define DEF_NUM_WORDS 2

/* length is the actual number of digits used by the bignum, by definition
 * zero uses zero digits. max_length is the actual length allocated currently
 * to the digits array. neg is nonzero if the bignum is negative, 0
 * otherwise. */
typedef struct bignum
{
     unsigned length;
     unsigned max_length;
     int neg;
     SHORT_INT_T *digits;
} BigNum;

/* makes a new zero bignum */
void init_bignum(BigNum *p);
/* makes a new bignum from a string, returns pointer to array */
void init_bignum_string(BigNum *p, char *string);
/* make new bignum from integer */
void init_bignum_int(BigNum *p, SHORT_INT_T n);
/* makes a new bignum of a given length initialised to 0 */
void alloc_zero_bignum(BigNum *p, int length);

void free_bignum(BigNum *p);

void print_bignum(BigNum p);

void bignum_copy(BigNum *d, BigNum *s);

int bignum_length(BigNum p);

/* logical operations */
int bignum_is_neg(BigNum p);
int bignum_equal(BigNum left, BigNum right);
int bignum_lt(BigNum left, BigNum right);
int bignum_gt(BigNum left, BigNum right);
int bignum_lte(BigNum left, BigNum right);
int bignum_gte(BigNum left, BigNum right);

/* arithmetic */
void negate_bignum(BigNum *p);
void add_bignums(BigNum *res, BigNum *left, BigNum *right);
void sub_bignums(BigNum *res, BigNum *left, BigNum *right);
void mul_bignums(BigNum *res, BigNum *left, BigNum *right);
void mul_bignums2(BigNum *res, BigNum *left, SHORT_INT_T right);
void div_bignums(BigNum *q, BigNum *r, BigNum left, BigNum *right);
void div_bignums2(BigNum *q, SHORT_INT_T *r, BigNum *left, SHORT_INT_T right);

void bn_power(BigNum *res, BigNum *p, SHORT_INT_T power);

void half_bignum(BigNum *res, BigNum *u);
void double_bignum(BigNum *res, BigNum *u);

/* greatest common divisor - binary method */
void gcd(BigNum *gcd, BigNum *u, BigNum *v);
/* greatest common divisor - Euclid's method */
void gcd2(BigNum *gcd, BigNum *u, BigNum *v);
/* least common multiple */
void lcm(BigNum *lcm, BigNum *u, BigNum *v);

/* other */
/* returns true is bignum is equal to zero */
int bignum_is_zero(BigNum u);
/* true if bignum is equal to one */
int bignum_is_one(BigNum u);

#endif /* _BIGNUM_H_ */
