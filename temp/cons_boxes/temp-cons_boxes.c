#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


char __curly_prim__getc(char* str, size_t i)
{
    return str[i];
}

char* __curly_prim__str_with_cap(size_t cap)
{
    return calloc(cap, sizeof(char));
}

void __curly_prim__setc(char* str, size_t i, char c)
{
    str[i] = c;
}

void __curly_prim__free(char* str)
{
    free(str);
}

void __curly_prim__print_str(char* str)
{
    printf("%s\n", str);
}

char* __curly_prim__null()
{
    return (char*) 0;
}

bool __curly_prim__is_null(char* s)
{
    return s == (char*) 0;
}
