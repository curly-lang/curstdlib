#include "types-collections-hashmap-backend.h"

#include <stdbool.h>
#include <stddef.h>

struct HashMap *__curly_HashMap_new()
{
    return hashMapNew();
}

void __curly_HashMap_free(struct HashMap *HashMap_to_free)
{
    hashMapFree(HashMap_to_free);
}



bool __curly_HashMap_insert(struct HashMap *HashMap_to_insert_to, const char *key, const char *value)
{
    return hashMapInsert(HashMap_to_insert_to, key, value);
}

bool __curly_HashMap_remove(struct HashMap *HashMap_to_remove_from, const char *key)
{
    return hashMapRemove(HashMap_to_remove_from, key);
}


char *__curly_HashMap_get(struct HashMap *HashMap_to_get_from, const char *key)
{
    return hashMapGet(HashMap_to_get_from, key);
}

const char **__curly_HashMap_keys(struct HashMap *HashMap_to_get_keys_from)
{
    return hashMapKeys(HashMap_to_get_keys_from);
}


void __curly_HashMap_print(struct HashMap *HashMap_to_print)
{
    return printHashMap(HashMap_to_print);
}
