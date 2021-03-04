CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -ltemp-cons_boxes

libs: temp-cons_boxes.c
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libtemp-cons_boxes.a temp-cons_boxes.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) temp-cons_boxes.curly test/temp-cons_boxes--test.curly

run: all
	./.build/main
