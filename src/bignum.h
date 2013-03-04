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
