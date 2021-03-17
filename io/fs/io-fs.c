#include "io-fs-path.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ftw.h>

#if defined(__APPLE__) || defined(__FreeBSD__)
    #include <copyfile.h>
#else
    #include <sys/sendfile.h>
#endif

int copyFile(char *src, char *dest)
{
    int input, output;
    if ((input = open(src, O_RDONLY)) == -1) {
        return -1;
    }
    if ((output = creat(dest, 0660)) == -1) {
        close(input);
        return -1;
    }

#if defined(__APPLE__) || defined(__FreeBSD__)
    int result = fcopyfile(input, output, 0, COPYFILE_ALL);
#else
    off_t bytesCopied = 0;
    struct stat fileinfo = {0};
    fstat(input, &fileinfo);
    int result = sendfile(output, input, &bytesCopied, fileinfo.st_size);
#endif /* defined(__APPLE__) || defined(__FreeBSD__) */

    close(input);
    close(output);

    return result;
}

bool __curly_copy_file(Path *srcPath, Path *destPath)
{
    char *srcString  = __curly_path_to_string(srcPath);
    char *destString = __curly_path_to_string(destPath);

    int copyResult = copyFile(srcString, destString);

    free(srcString);
    free(destString);

    return copyResult == 0;
}

bool __curly_rename_file(Path *srcPath, Path *destPath)
{
    char *srcString  = __curly_path_to_string(srcPath);
    char *destString = __curly_path_to_string(destPath);
    int returnValue = rename(srcString, destString);

    free(srcString);
    free(destString);

    return returnValue == 0;
}

bool __curly_create_dir(Path *dirPath)
{
    char *dirString = __curly_path_to_string(dirPath);

    int result;

    struct stat st = {0};

    if (stat(dirString, &st) == -1)
        result = mkdir(dirString, 0755);
    else
        result = -1;

    return result == 0;
}

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int rv = remove(fpath);

    return rv;
}

bool __curly_remove_dir(Path *dirPath)
{
    char *dirString = __curly_path_to_string(dirPath);

    int returnValue = nftw(dirString, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);

    free(dirString);

    return returnValue == 0;
}

bool __curly_remove_file(Path *filePath)
{
    char *fileString = __curly_path_to_string(filePath);

    int returnValue = remove(fileString);

    free(fileString);

    return returnValue == 0;
}

Path *__curly_canonicalize(Path *pathToCanonicalize)
{
    char *stringToCanonicalize = __curly_path_to_string(pathToCanonicalize);

    char *canonicalizedString = realpath(stringToCanonicalize, NULL);
    free(stringToCanonicalize);

    Path *canonicalizedPath = __curly_string_to_path(canonicalizedString);
    free(canonicalizedString);

    return canonicalizedPath;
}

char __curly_file_type(Path *find)
{
    struct stat buf;
    lstat ("junklink", &buf);
    
    switch (buf.st_mode & S_IFMT) {
        case S_IFBLK:  return 'B' ; break;
        case S_IFCHR:  return 'C' ; break;
        case S_IFDIR:  return 'D' ; break;
        case S_IFIFO:  return 'f' ; break;
        case S_IFLNK:  return 'L' ; break;
        case S_IFREG:  return 'F' ; break;
        case S_IFSOCK: return 'S' ; break;
        default:       return '\0'; break;
    }
}
