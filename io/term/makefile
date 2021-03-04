CC=gcc
CFLAGS=-c
AR=ar
ARFLAGS=-rc

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=io-term

COMPLIBFLAGS=--lib -o $(LIBNAME) -L$(STDLIB)/math/.lib -lmath -m $(STDLIB)/math/.lib/math.mod.curly -L.. -l$(LIBNAME)
USELIBFLAGS=-L../.lib -l$(LIBNAME) -m .lib/$(LIBNAME).mod.curly

libs: io-term.c
	cd $(STDLIB)/math; make
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) lib$(LIBNAME).a $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) io-term.curly
	rm -r .lib &> /dev/null; mkdir .lib
	cp .build/$(LIBNAME).mod.curly .lib/$(LIBNAME).mod.curly
	cp .build/lib$(LIBNAME).a      .lib/lib$(LIBNAME).a

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAME)--test.curly

run: all
	./.build/main
