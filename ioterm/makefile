CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lioterm

libs: ioterm.c
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libioterm.a ioterm.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) ioterm.curly test/ioterm_test.curly

run: all
	./.build/main
