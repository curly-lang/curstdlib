CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lcurl -L../../../temp/cons_boxes/ -lcons

libs:
	cd ../../math; make
	cd ../../temp/cons_boxes; make
	# $(CC) $(CFLAGS) $?
	# $(AR) $(ARFLAGS) libioterm.a ioterm.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) curl.curly ../../temp/cons_boxes/temp-cons_boxes.curly test/curl_test.curly

run: all
	./.build/main

