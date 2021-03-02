CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -lioterm -L../../cons_boxes -lcons -L../../../ioterm/ -lioterm

libs:
	cd ../cons_boxes; make
	cd ../../ioterm; make

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) ../../ioterm/ioterm.curly ../cons_boxes/cons_boxes.curly ioterm.curly test/ioterm_test.curly

run: all
	./.build/main

