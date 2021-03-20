#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

void __curly_gtk_init()
{
    char** argv = calloc(1, sizeof(char*));
    argv[0] = calloc(1, sizeof(char));
    gtk_init(0, &argv);
}

