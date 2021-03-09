CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=IO::Term
LIBNAMEREDUCED=io-term

LIBMATH=-m $(STDLIB)/math/.lib/Math.curlylib

COMPLIBFLAGS=--lib -o $(LIBNAME) -l $(LIBNAME).o $(LIBMATH)
USELIBFLAGS=-m .lib/$(LIBNAME).curlylib

libs: $(LIBNAMEREDUCED).c
	cd $(STDLIB)/math; make
	$(CC) $(CFLAGS) $? -o $(LIBNAME).o
	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly
	rm -r .lib; mkdir .lib
	cp .build/$(LIBNAME).curlylib .lib/$(LIBNAME).curlylib 

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main
