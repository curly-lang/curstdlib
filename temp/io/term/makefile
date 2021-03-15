CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=Temp::IO::Term
LIBNAMEREDUCED=temp-io-term


LIBIO-TERM=-m $(STDLIB)/io/term/.lib/IO::Term.curlylib
LIBTEMP-CONS_BOXES=-l $(STDLIB)/temp/cons_boxes/Temp::Cons_Boxes.o $(STDLIB)/temp/cons_boxes/temp-cons_boxes.curly

COMPLIBFLAGS=--lib -o $(LIBNAME) $(LIBIO-TERM) $(LIBTEMP-CONS_BOXES)
USELIBFLAGS=$(LIBIO-TERM) $(LIBTEMP-CONS_BOXES) $(LIBNAMEREDUCED).curly


libs:
	cd $(STDLIB)/temp/cons_boxes; make
	cd $(STDLIB)/io/term;         make

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly
	rm -r .lib > /dev/null 2>&1; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main
