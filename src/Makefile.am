## Process this file with automake to produce Makefile.in

CC = gcc
CCAS = gcc

BUILT_SOURCES = parser.h
AM_YFLAGS = -d

bin_PROGRAMS = bignums

GCCFLAGS = -Wall
AM_CPPFLAGS = $(GCCFLAGS)
AM_CFLAGS = $(GCCFLAGS)
AM_CCASFLAGS = $(GCCFLAGS)

bignums_SOURCES = alg.l parser.y bignum.h natural.h integer.h zinit.c zio.c	\
                  addorsub.h zadd.c zsub.c zmul.c zdiv.c zshift.c zpower.c	\
                  zlogic.c zasgn.c memory.h memory.c test.h

EXTRA_bignums_SOURCES = generic/test.c          x86_64/test.s       arm/test.s	\
                        generic/ndiv.c          x86_64/ndiv.c \
                        generic/ndiv2.c         x86_64/ndiv2.c \
                        generic/dig_div.c \
                        generic/nlz.c           x86_64/nlz.c \
			generic/nadd.c          x86_64/nadd.s \
			generic/nadd2.c	        x86_64/nadd2.s \
			generic/ncmp.c          x86_64/ncmp.s \
			generic/nmul.c          x86_64/nmul.c \
			generic/nmul2.c         x86_64/nmul2.c \
			generic/dig_mul.c       x86_64/dig_mul.c \
			generic/dig_mulandadd.c x86_64/dig_mulandadd.c \
			generic/nlshift.c \
			generic/nrshift.c \
			generic/nsub.c          x86_64/nsub.s    \
			generic/nsub2.c         x86_64/nsub2.s

OBJS = $(TEST_OBJ) $(NDIV_OBJ) $(NDIV2_OBJ) $(DIG_DIV_OBJ) $(NLZ_OBJ)		\
       $(NADD_OBJ) $(NADD2_OBJ) $(NCMP_OBJ) $(NMUL_OBJ) $(NMUL2_OBJ)		\
       $(DIG_MUL_OBJ) $(DIG_MULANDADD_OBJ) $(NLSHIFT_OBJ) $(NRSHIFT_OBJ)	\
       $(NSUB_OBJ) $(NSUB2_OBJ)

bignums_LDADD = $(OBJS)
bignums_DEPENDENCIES = $(OBJS)

mostlyclean-local:
	rm -f generic/*.o x86_64/*.o arm/*.o
