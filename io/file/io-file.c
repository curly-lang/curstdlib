#include <stdio.h>
#include <stdbool.h>


FILE* __curly_open_file(char* file, char* type)
{
    return fopen(file, type);
}

bool __curly_is_null_fileptr(FILE* file)
{
    return (file == 0);
}

void __curly_close_file(FILE* file)
{
    fclose(file);
}

bool __curly_is_eof(FILE* file)
{
    return feof(file);
}

bool __curly_is_err(FILE* file)
{
    return ferror(file);
}

char __curly_get_char(FILE* file)
{
    int c = fgetc(file);
    if (feof(file)) {
        return 0;
    }
    return c;
}

bool __curly_put_char(FILE* file, char c)
{
    return fputc(c, file) != EOF;
}

bool __curly_seek(FILE* file, unsigned long origin_num, long offset)
{
    int origin;
    if (origin_num == 0) {
        origin = SEEK_SET;
    } else if (origin_num == 1) {
        origin = SEEK_CUR;
    } else {
        origin = SEEK_END;
    }
    int ret_code = fseek(file, offset, origin);
    return !ret_code;
}
