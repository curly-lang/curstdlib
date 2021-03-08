CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=Math

COMPLIBFLAGS=--lib -o $(LIBNAME) -L ..
USELIBFLAGS=-m $(STDLIB)/math/.lib/Math.curlylib

libs:
	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) math.curly
	rm -r .lib &> /dev/null; mkdir .lib
#	cp .build/$(LIBNAME).mod.curly .lib/$(LIBNAME).mod.curly
#	cp .build/lib$(LIBNAME).a      .lib/lib$(LIBNAME).a
	cp .build/$(LIBNAME).curlylib  .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAME)_test.curly

run: all
	./.build/main


