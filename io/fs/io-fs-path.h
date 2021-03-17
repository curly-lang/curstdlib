#ifndef IO_FS_PATH__INCLUDED
#define IO_FS_PATH__INCLUDED




#define Path struct PathStruct
#define PathNode struct PathNodeStruct

#ifdef _WIN32
    #define pathSeperator '\\'
#else
    #define pathSeperator '/'
#endif /* _WIN32 */


struct PathNodeStruct {
    char *nodeContents;
    PathNode *nextNode;
};

struct PathStruct {
    char root;
    PathNode *nextNode;
};


char getPathRootType(char);
int getPathStrLen(Path *);

char *__curly_get_home_dir();
char *__curly_path_to_string(Path *);
Path *__curly_string_to_path(char *);
void __curly_free_path(Path *);
Path *__curly_copy_path(Path *);




#endif /* IO_FS_PATH__INCLUDED */
