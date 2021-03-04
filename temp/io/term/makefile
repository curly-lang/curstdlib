CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURSTDLIB=~/curstdlib
CURLYFLAGS=-L$.. -L$(CURSDLIB)/temp/cons_boxes -ltemp-cons-boxes -L$(CURSTDLIB)/io/term/ -lio-term

libs:
	cd $(CURSTDLIB)/temp/cons_boxes; make
	cd $(CURSTDLIB)/io/term;         make

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) $(CURSTDLIB)/io/term/io-term.curly $(CURSTDLIB)/temp/cons_boxes/temp-cons_boxes.curly temp-io-term.curly test/temp-io-term--test.curly

run: all
	./.build/main

