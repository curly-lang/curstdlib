CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lcons

libs: cons_boxes.c
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libcons.a cons_boxes.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) cons_boxes.curly test/cons_boxes_test.curly

run: all
	./.build/main
