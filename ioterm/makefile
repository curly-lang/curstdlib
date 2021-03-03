CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lioterm -L../../math -lmath

libs: ioterm.c
	cd ../math; make
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libioterm.a ioterm.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) ../math/math.curly ioterm.curly test/ioterm_test.curly

run: all
	./.build/main
