## Process this file with automake to produce Makefile.in

CC = gcc
CCAS = gcc

BUILT_SOURCES = parser.h
AM_YFLAGS = -d

bin_PROGRAMS = bignums

GCCFLAGS = -Wall -Werror
AM_CPPFLAGS = $(GCCFLAGS)
AM_CFLAGS = $(GCCFLAGS)
AM_CCASFLAGS = $(GCCFLAGS)

bignums_SOURCES = alg.l parser.y bignum.h natural.h integer.h zinit.c zio.c	\
                  addorsub.h zadd.c zsub.c zmul.c zdiv.c zpower.c zlogic.c	\
                  zasgn.c memory.h memory.c test.h

EXTRA_bignums_SOURCES = generic/test.c     x86_64/test.s arm/test.s	\
                        generic/ndiv.c     x86_64/ndiv.c \
			generic/nadd.c \
			generic/nlogic.c \
			generic/nmul.c \
			generic/nshift.c \
			generic/nsub.c

OBJS = $(TEST_OBJ) $(NDIV_OBJ) $(NADD_OBJ) $(NLOGIC_OBJ) $(NMUL_OBJ) \
       $(NSHIFT_OBJ) $(NSUB_OBJ)

bignums_LDADD = $(OBJS)
bignums_DEPENDENCIES = $(OBJS)

mostlyclean-local:
	rm -f generic/*.o x86_64/*.o arm/*.o
