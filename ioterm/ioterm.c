#include <stdio.h>
#include <sys/ioctl.h>


void __curly_prim__putch(char c)
{
    printf("%c", c);
}

char __curly_prim__getch()
{
    return getchar();
}    


struct winsize sz;

int __curly_prim__cols()
{
    ioctl( 0, TIOCGWINSZ, &sz );
    return sz.ws_col;
}

int __curly_prim__rows()
{
    ioctl( 0, TIOCGWINSZ, &sz );
    return sz.ws_row;
}
