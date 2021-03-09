CC=gcc
CFLAGS=-c -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pango-1.0/ -I/usr/include/harfbuzz -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/atk-1.0
MACOSCFLAGS=-I/opt/homebrew/include -I/opt/homebrew/include/gtk-3.0 -I/opt/homebrew/include/glib-2.0 -I/opt/homebrew/lib/glib-2.0/include -I/opt/homebrew/include/pango-1.0/ -I/opt/homebrew/include/harfbuzz -I/opt/homebrew/include/cairo -I/opt/homebrew/include/gdk-pixbuf-2.0 -I/opt/homebrew/include/atk-1.0
AR=ar
ARFLAGS=-rc
CURLYC_DEBUG=RUST_BACKTRACE=1 ~/curly-lang/target/debug/curlyc
CURLYC=~/curly-lang/target/debug/curlyc
CURLYFLAGS=-L.. -l:libgtk-3.so -lgtkbind -L../../../temp/cons_boxes/ -lcons

libs: gtkbind.c
	cd ../../temp/cons_boxes; make

	$(CC) $(CFLAGS) $(MACOSCFLAGS) $?
	$(AR) $(ARFLAGS) libgtkbind.a gtkbind.o

all: libs
	$(CURLYC_DEBUG) build $(CURLYFLAGS) gtk.curly ../../temp/cons_boxes/temp-cons_boxes.curly test/gtk_test.curly

run: all
	./.build/main

