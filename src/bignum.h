/* bignums are arbitrary precision integers */
/* **TODO**: make sure this works with any system not just mine,
     probably using a configure script to work out which types to use
     and the radix */

#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#include <limits.h>

/* config from autoconf */
#include <config.h>

/* and the argument type for printf */
#define PRINT_LI(var) printf("%lu", var)

/* signed version for checking sign of bignum */
/* and its argument for printf */
#define PRINT_SI(var) printf("%lu", var)


/* system specific options */

/* generic settings that should work on 32 bit systems */
#ifdef SYSTEM_GENERIC
   /* short int type for storage */
   #define SHORT_INT_T unsigned int
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
#endif  /* SYSTEM_GENERIC */

/* x86-64 */
#ifdef SYSTEM_X86_64
   #define SHORT_INT_T unsigned long int
   #define SRADIX  0x100000000u
   #define GRPOW10   10000000000000000000u
   #define GRPOW10DIGS 19
   #define GRPOW10DIGSB2 64
   #define WORD_LENGTH 64
#endif  /* SYSTEM_X86_64 */

/* ARM */
#ifdef SYSTEM_ARM
   #define SHORT_INT_T unsigned int
   #define SRADIX  0x10000
   #define GRPOW10   1000000000
   #define GRPOW10DIGS 9
   #define GRPOW10DIGSB2 30
   #define WORD_LENGTH 32
#endif  /* SYSTEM_ARM */

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

/* Local Variables: */
/* mode: c */
/* End: */
