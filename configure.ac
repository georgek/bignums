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
NADD_OBJ='generic/nadd.$(OBJEXT)'
NLOGIC_OBJ='generic/nlogic.$(OBJEXT)'
NMUL_OBJ='generic/nmul.$(OBJEXT)'
NSHIFT_OBJ='generic/nshift.$(OBJEXT)'
NSUB_OBJ='generic/nsub.$(OBJEXT)'

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
       NMUL_OBJ='x86_64/nmul.$(OBJEXT)'
       NADD_OBJ='x86_64/nadd.$(OBJEXT)'
       ;;
     *-*-*)
       AC_DEFINE([SYSTEM_GENERIC], [1], [Generic system.])
   esac
   AC_SUBST([TEST_OBJ])
   AC_SUBST([NDIV_OBJ])
   AC_SUBST([NADD_OBJ])
   AC_SUBST([NLOGIC_OBJ])
   AC_SUBST([NMUL_OBJ])
   AC_SUBST([NSHIFT_OBJ])
   AC_SUBST([NSUB_OBJ])            
])

AS_IF([test "x$enable_arch" = "xno"], [
    AC_DEFINE([SYSTEM_GENERIC], [1], [Generic system.])
])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
