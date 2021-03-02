CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L..

libs:

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) math.curly test/math_test.curly

run: all
	./.build/main


