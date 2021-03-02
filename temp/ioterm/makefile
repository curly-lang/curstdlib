CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -L../../cons_boxes -lcons -L../../../ioterm/ -lioterm

libs:
	cd ../cons_boxes; make
	cd ../../ioterm; make

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) ../cons_boxes/cons_boxes.curly test/ioterm_test.curly ../../ioterm/ioterm.curly

run: all
	./.build/main

