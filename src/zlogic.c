/* Logic functions for integers. */

#include "bignum.h"
#include "integer.h"

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

int bignum_equal(BigNum left, BigNum right)
{
     return left.length == right.length &&
          left.neg == right.neg &&
          bignum_ncmp(left,right) == 0;
}

int bignum_lt(BigNum left, BigNum right)
{
     switch (left.neg - right.neg) {
     case 1:                    /* left neg, right pos */
          return 1;
     case 0:                    /* same signs */
          switch ((left.length>right.length)-(left.length<right.length)) {
          case 1:               /* left longer than right (result depends on
                                 * sign) */
               return left.neg;
          case 0:               /* same length */
               /* flip result if both are negative */
               return bignum_ncmp(left,right)-(left.neg<<1) == -1;
          case -1:              /* right longer than left */
               return !left.neg;
          }
     case -1:                   /* left pos, right neg */
          return 0;
     }
}

int bignum_gt(BigNum left, BigNum right)
{
     switch (left.neg - right.neg) {
     case 1:                    /* left neg, right pos */
          return 0;
     case 0:                    /* same signs */
          switch ((left.length>right.length)-(left.length<right.length)) {
          case 1:               /* left longer than right (result depends on
                                 * sign) */
               return !left.neg;
          case 0:               /* same length */
               /* flip result if both are negative */
               return bignum_ncmp(left,right)+(left.neg<<1) == 1;
          case -1:              /* right longer than left */
               return left.neg;
          }
     case -1:                   /* left pos, right neg */
          return 1;
     }
}

int bignum_lte(BigNum left, BigNum right)
{
     switch (left.neg - right.neg) {
     case 1:                    /* left neg, right pos */
          return 1;
     case 0:                    /* same signs */
          switch ((left.length>right.length)-(left.length<right.length)) {
          case 1:               /* left longer than right (result depends on
                                 * sign) */
               return left.neg;
          case 0:               /* same length */
               /* flip result if both are negative */
               return bignum_ncmp(left,right)-(left.neg<<1) <= 0;
          case -1:              /* right longer than left */
               return !left.neg;
          }
     case -1:                   /* left pos, right neg */
          return 0;
     }
}

int bignum_gte(BigNum left, BigNum right)
{
     switch (left.neg - right.neg) {
     case 1:                    /* left neg, right pos */
          return 0;
     case 0:                    /* same signs */
          switch ((left.length>right.length)-(left.length<right.length)) {
          case 1:               /* left longer than right (result depends on
                                 * sign) */
               return !left.neg;
          case 0:               /* same length */
               /* flip result if both are negative */
               return bignum_ncmp(left,right)+(left.neg<<1) >= 0;
          case -1:              /* right longer than left */
               return left.neg;
          }
     case -1:                   /* left pos, right neg */
          return 1;
     }
}