CC=gcc
CFLAGS=-c

CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

STDLIB=~/curstdlib
LIBNAME=IO::FS
LIBNAMEREDUCED=io-fs

LIBTEMP-CONS_BOXES=-l $(STDLIB)/temp/cons_boxes/Temp::Cons_Boxes.o $(STDLIB)/temp/cons_boxes/temp-cons_boxes.curly
LIBIO-FILE=-l $(STDLIB)/io/file/IO::File.o $(STDLIB)/io/file/io-file.curly

COMPLIBFLAGS=$(LIBTEMP-CONS_BOXES)  $(LIBIO-FILE)  -l $(LIBNAME).o -l $(LIBNAME)::Path.o  --lib -o $(LIBNAME)
USELIBFLAGS= $(LIBTEMP-CONS_BOXES)  $(LIBIO-FILE)  -l $(LIBNAME).o -l $(LIBNAME)::Path.o  $(LIBNAMEREDUCED).curly

libs:
	cd $(STDLIB)/temp/cons_boxes; make

	$(CC) $(CFLAGS) $(LIBNAMEREDUCED)-path.c -o $(LIBNAME)::Path.o
	$(CC) $(CFLAGS) $(LIBNAMEREDUCED).c      -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly

	rm -r .lib; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main

