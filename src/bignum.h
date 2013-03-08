/* bignums are arbitrary precision integers */
/* **TODO**: make sure this works with any system not just mine,
     probably using a configure script to work out which types to use
     and the radix */

#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include <limits.h>

/* and the argument type for printf */
#define PRINT_LI(var) printf("%lu", var)

/* short int type for storage */
#define SHORT_INT_T unsigned int
/* signed version for checking sign of bignum */
/* and its argument for printf */
#define PRINT_SI(var) printf("%u", var)

/* radix of full words */
/* #define RADIX   0x100000000 */
/* radix of half words */
#define SRADIX  0x10000
/* greatest power of ten that can fit in a word */
#define GRPOW10   1000000000
/* number of digits in base 10 in the grpow10 */
#define GRPOW10DIGS 9
/* number of digits in base 2 in the grpow10 */
#define GRPOW10DIGSB2 30
/* word length is the actual length of SHORT_INT_T in bits */
#define WORD_LENGTH 32

/* number of words that bignums start with */
#define DEF_NUM_WORDS 8

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

#endif /* _BIGNUM_H_ */
