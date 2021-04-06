CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=Types::Collections::HashMap
LIBNAMEREDUCED=types-collections-hashmap

LIBTEMP-CONS_BOXES=-m $(STDLIB)/temp/cons_boxes/.lib/Temp::Cons_Boxes.curlylib

COMPLIBFLAGS=$(LIBTEMP-CONS_BOXES) -l $(LIBNAME).o -l $(LIBNAME)::Backend.o  --lib -o $(LIBNAME)
USELIBFLAGS= -m .lib/$(LIBNAME).curlylib

libs:
	cd $(STDLIB)/temp/cons_boxes/; make

	$(CC) $(CFLAGS) $(LIBNAMEREDUCED)-backend.c -o $(LIBNAME)::Backend.o
	$(CC) $(CFLAGS) $(LIBNAMEREDUCED).c      -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly

	rm -r .lib > /dev/null 2>&1; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main

