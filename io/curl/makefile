CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=io-curl

LIBTEMP-CONS_BOXES=-L$(STDLIB)/temp/cons_boxes/.lib -ltemp-cons_boxes -m $(STDLIB)/temp/cons_boxes/.lib/temp-cons_boxes.mod.curly

COMPLIBFLAGS=-L.. -l$(LIBNAME) $(LIBTEMP-CONS_BOXES)
USELIBFLAGS=-L../.lib -l$(LIBNAME) -m .lib/$(LIBNAME).mod.curly

libs:
	cd $(STDLIB)/temp/cons_boxes; make

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAME).curly
	rm -r .lib &> /dev/null; mkdir .lib
	cp .build/$(LIBNAME).mod.curly .lib/$(LIBNAME).mod.curly
	cp .build/lib$(LIBNAME).a      .lib/lib$(LIBNAME).a

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) test/$(LIBNAME)--test.curly

run: all
	./.build/main

