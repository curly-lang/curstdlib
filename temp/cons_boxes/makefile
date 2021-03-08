CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

LIBNAME=Temp::Cons_Boxes
LIBNAMEREDUCED=temp-cons_boxes

COMPLIBFLAGS=--lib -o $(LIBNAME) -l $(LIBNAME).o
USELIBFLAGS=-l $(LIBNAME).o -m .lib/$(LIBNAME).curlylib


libs: $(LIBNAMEREDUCED).c
	$(CC) $(CFLAGS) $? -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly

	rm -r .lib &> /dev/null; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main
