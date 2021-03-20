CC=gcc


IPATH=/usr/include
MACOSIPATH=/opt/homebrew/include

CFLAGS=-c -I$(IPATH)/gtk-3.0 -I$(IPATH)/glib-2.0 -I/usr/lib/glib-2.0/include -I$(IPATH)/pango-1.0/ -I$(IPATH)/harfbuzz -I$(IPATH)/cairo -I$(IPATH)/gdk-pixbuf-2.0 -I$(IPATH)/atk-1.0
MACOSCFLAGS=-I$(MACOSIPATH) -I$(MACOSIPATH)/gtk-3.0 -I$(MACOSIPATH)/glib-2.0 -I/opt/homebrew/lib/glib-2.0/include -I$(MACOSIPATH)/pango-1.0/ -I$(MACOSIPATH)/harfbuzz -I$(MACOSIPATH)/cairo -I$(MACOSIPATH)/gdk-pixbuf-2.0 -I$(MACOSIPATH)/atk-1.0


CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc


STDLIB=~/curstdlib
LIBNAME=IO::GTK
LIBNAMEREDUCED=io-gtk


LIBTEMP-CONS_BOXES=-m $(STDLIB)/temp/cons_boxes/.lib/Temp::Cons_Boxes.curlylib

SHAREDLIBS=-L/usr/lib -L/opt/homebrew/lib -lgtk-3 -lgobject-2.0

COMPLIBFLAGS=$(LIBTEMP-CONS_BOXES)  $(SHAREDLIBS)  -l $(LIBNAME).o  --lib -o $(LIBNAME)
USELIBFLAGS= $(SHAREDLIBS)  -m $(STDLIB)/io/gtk/.lib/$(LIBNAME).curlylib


libs: io-gtk.c
	cd ../../temp/cons_boxes; make

	$(CC) $(CFLAGS) $(MACOSCFLAGS) $? -o $(LIBNAME).o

	$(CURLYC_DEBUG) build $(COMPLIBFLAGS) $(LIBNAMEREDUCED).curly

	rm -r .lib > /dev/null 2>&1; mkdir .lib
	cp .build/$(LIBNAME).curlylib      .lib/$(LIBNAME).curlylib

all: libs
	$(CURLYC_DEBUG) build $(USELIBFLAGS) test/$(LIBNAMEREDUCED)--test.curly

run: all
	./.build/main

