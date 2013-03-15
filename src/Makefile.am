## Process this file with automake to produce Makefile.in

CC = gcc
CCAS = gcc

BUILT_SOURCES = parser.h
AM_YFLAGS = -d

bin_PROGRAMS = bignums

bignums_SOURCES = alg.l parser.y bignum.h natural.h nadd.c nsub.c nmul.c	\
                  nlogic.c nshift.c integer.h zinit.c zio.c zadd.c zsub.c	\
                  zmul.c zdiv.c zpower.c zlogic.c zasgn.c memory.h memory.c	\
                  test.h

EXTRA_bignums_SOURCES = generic/test.c x86_64/test.s arm/test.s	\
                        generic/ndiv.c x86_64/ndiv.c

bignums_LDADD = $(TEST_OBJ) $(NDIV_OBJ)
bignums_DEPENDENCIES = $(TEST_OBJ) $(NDIV_OBJ)
