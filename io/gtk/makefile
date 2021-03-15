CC=gcc


IPATH=/usr/include
MACOSIPATH=/opt/homebrew/include

CFLAGS=-c -I$(IPATH)/gtk-3.0 -I$(IPATH)/glib-2.0 -I/usr/lib/glib-2.0/include -I$(IPATH)/pango-1.0/ -I$(IPATH)/harfbuzz -I$(IPATH)/cairo -I$(IPATH)/gdk-pixbuf-2.0 -I$(IPATH)/atk-1.0
MACOSCFLAGS=-I$(MACOSIPATH) -I$(MACOSIPATH)/gtk-3.0 -I$(MACOSIPATH)/glib-2.0 -I/opt/homebrew/lib/glib-2.0/include -I$(MACOSIPATH)/pango-1.0/ -I$(MACOSIPATH)/harfbuzz -I$(MACOSIPATH)/cairo -I$(MACOSIPATH)/gdk-pixbuf-2.0 -I$(MACOSIPATH)/atk-1.0


AR=ar
ARFLAGS=-rc


CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc

CURLYFLAGS=-L.. -lgtkbind -L/usr/lib -L/opt/homebrew/lib -lgtk-3  -lgobject-2.0 -l $(STDLIB)/temp/cons_boxes/Temp::Cons_Boxes.o
STDLIB=~/curstdlib

libs: gtkbind.c
	cd ../../temp/cons_boxes; make

	$(CC) $(CFLAGS) $(MACOSCFLAGS) $?
	$(AR) $(ARFLAGS) libgtkbind.a gtkbind.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) gtk.curly ../../temp/cons_boxes/temp-cons_boxes.curly test/gtk_test.curly

run: all
	./.build/main

