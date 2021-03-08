CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=IO::Curl

LIBTEMP-CONS_BOXES=-m $(STDLIB)/temp/cons_boxes/.lib/Temp::Cons_Boxes.curlylib

COMPLIBFLAGS=-l $(LIBNAME) $(LIBTEMP-CONS_BOXES)
USELIBFLAGS=-m .lib/$(LIBNAME).mod.curly

libs:
	cd $(STDLIB)/temp/cons_boxes; make
	$(CC) $(CFLAGS) $? -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAME).curly

	rm -r .lib &> /dev/null; mkdir .lib
	cp .build/$(LIBNAME).mod.curly .lib/$(LIBNAME).mod.curly
	cp .build/lib$(LIBNAME).a      .lib/lib$(LIBNAME).a

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) test/$(LIBNAME)--test.curly

run: all
	./.build/main

