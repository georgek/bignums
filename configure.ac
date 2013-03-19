# prelude
AC_INIT([bignums], [1.0], [g.kettleborough@uea.ac.uk])
AC_CONFIG_SRCDIR([src/bignum.h])
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects])

AM_SILENT_RULES([yes])

# check for programs: C compiler, assembler, lex, yacc
AM_PROG_CC_C_O
AM_PROG_AS
AC_PROG_LEX
AC_PROG_YACC

# check for GNU readline
AC_CHECK_LIB([readline], [readline])

# system specific sources, by default we take from generic/
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

TEST_OBJ='generic/test.$(OBJEXT)'
NDIV_OBJ='generic/ndiv.$(OBJEXT)'
NDIV2_OBJ='generic/ndiv2.$(OBJEXT)'
DIG_DIV_OBJ='generic/dig_div.$(OBJEXT)'
NLZ_OBJ='generic/nlz.$(OBJEXT)'
NADD_OBJ='generic/nadd.$(OBJEXT)'
NADD2_OBJ='generic/nadd2.$(OBJEXT)'
NCMP_OBJ='generic/ncmp.$(OBJEXT)'
NMUL_OBJ='generic/nmul.$(OBJEXT)'
NMUL2_OBJ='generic/nmul2.$(OBJEXT)'
DIG_MUL_OBJ='generic/dig_mul.$(OBJEXT)'
DIG_MULANDADD_OBJ='generic/dig_mulandadd.$(OBJEXT)'
NLSHIFT_OBJ='generic/nlshift.$(OBJEXT)'
NRSHIFT_OBJ='generic/nrshift.$(OBJEXT)'
NSUB_OBJ='generic/nsub.$(OBJEXT)'
NSUB2_OBJ='generic/nsub2.$(OBJEXT)'

AC_ARG_ENABLE([arch],
    AS_HELP_STRING([--disable-arch], [Disable arch specific optimisations.]))

AS_IF([test "x$enable_arch" != "xno"], [
   case $host in
     arm*-*-linux*)
       AC_DEFINE([SYSTEM_ARM], [1], [ARM system.])
       TEST_OBJ='arm/test.$(OBJEXT)'
       ;;
     x86_64-*-linux*)
       AC_DEFINE([SYSTEM_X86_64], [1], [x86-64 system.])
       TEST_OBJ='x86_64/test.$(OBJEXT)'
       NDIV_OBJ='x86_64/ndiv.$(OBJEXT)'
       NDIV2_OBJ='x86_64/ndiv2.$(OBJEXT)'
       DIG_DIV_OBJ=''
       NLZ_OBJ='x86_64/nlz.$(OBJEXT)'
       NMUL_OBJ='x86_64/nmul.$(OBJEXT)'
       NMUL2_OBJ='x86_64/nmul2.$(OBJEXT)'
       DIG_MUL_OBJ='x86_64/dig_mul.$(OBJEXT)'
       DIG_MULANDADD_OBJ='x86_64/dig_mulandadd.$(OBJEXT)'
       NADD_OBJ='x86_64/nadd.$(OBJEXT)'
       NADD2_OBJ='x86_64/nadd2.$(OBJEXT)'
       ;;
     *-*-*)
       AC_DEFINE([SYSTEM_GENERIC], [1], [Generic system.])
   esac
   AC_SUBST([TEST_OBJ])
   AC_SUBST([NDIV_OBJ])
   AC_SUBST([NDIV2_OBJ])
   AC_SUBST([DIG_DIV_OBJ])
   AC_SUBST([NLZ_OBJ])
   AC_SUBST([NADD_OBJ])
   AC_SUBST([NADD2_OBJ])
   AC_SUBST([NCMP_OBJ])
   AC_SUBST([NMUL_OBJ])
   AC_SUBST([NMUL2_OBJ])
   AC_SUBST([DIG_MUL_OBJ])
   AC_SUBST([DIG_MULANDADD_OBJ])
   AC_SUBST([NLSHIFT_OBJ])
   AC_SUBST([NRSHIFT_OBJ])
   AC_SUBST([NSUB_OBJ])
   AC_SUBST([NSUB2_OBJ])
])

AS_IF([test "x$enable_arch" = "xno"], [
    AC_DEFINE([SYSTEM_GENERIC], [1], [Generic system.])
])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
