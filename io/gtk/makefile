CC=gcc
CFLAGS=-c -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pango-1.0/ -I/usr/include/harfbuzz -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -l:libgtk-3.so -lgtkbind -L../../../temp/cons_boxes/ -lcons

libs: gtkbind.c
	cd ../../temp/cons_boxes; make
	$(CC) $(CFLAGS) $?
	$(AR) $(ARFLAGS) libgtkbind.a gtkbind.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) gtk.curly ../../temp/cons_boxes/cons_boxes.curly test/gtk_test.curly

run: all
	./.build/main

