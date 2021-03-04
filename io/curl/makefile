CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lcurl -lcurlbind -L../../../temp/cons_boxes/ -lcons
CFLAGS=-c
ARFLAGS=-rc

libs: curl.c
	cd ../../math; make
	cd ../../temp/cons_boxes; make
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libcurlbind.a curl.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) curl.curly test/curl_test.curly ../../temp/cons_boxes/temp-cons_boxes.curly

run: all
	./.build/main

