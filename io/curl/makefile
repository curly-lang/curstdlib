CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=IO::Curl
LIBNAMEREDUCED=io-curl

LIBTEMP-CONS_BOXES=-l $(STDLIB)/temp/cons_boxes/Temp::Cons_Boxes.o $(STDLIB)/temp/cons_boxes/temp-cons_boxes.curly

COMPLIBFLAGS=--lib -o $(LIBNAME) -lcurl -l $(LIBNAME).o $(LIBTEMP-CONS_BOXES)
USELIBFLAGS=-lcurl  -m .lib/$(LIBNAME).curlylib

libs: $(LIBNAMEREDUCED).c
	cd $(STDLIB)/temp/cons_boxes; make
	$(CC) $(CFLAGS) $? -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly

	rm -r .lib > /dev/null 2>&1; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main
