#ifndef COLLECTIONS_HASHMAP_BACKEND__INCLUDED
#define COLLECTIONS_HASHMAP_BACKEND__INCLUDED

#include <stdbool.h>
#include <stddef.h>

struct HashMapListItem
{
    char *key;
    char *value;
    bool initialized;
};

struct HashMap
{
    char bitSize;
    size_t slotsFilled;
    size_t a;
    struct HashMapListItem* list;
};

struct HashMap *hashMapNew();
void hashMapFree(struct HashMap*);

bool hashMapInsert(struct HashMap*, const char*, const char*);
bool hashMapRemove(struct HashMap*, const char*);

char *hashMapGet(struct HashMap*, const char*);
const char **hashMapKeys(struct HashMap*);

void printHashMap(struct HashMap*);

#endif /* COLLECTIONS_HASHMAP_BACKEND__INCLUDED */
