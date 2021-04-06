#include "types-collections-hashmap-backend.h"

#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define STARTING_BITS 3

size_t randomsize_t()
{
    return (((((((((size_t) rand()) << 15) + rand()) << 15) + rand()) << 15) + rand()) << 15) + rand();
}

size_t hashStr(const char *x, char M, size_t a)
{
    size_t h = 0;
    size_t mask = ((size_t) 1 << M) - 1;
    for (size_t i=0 ; i < strlen(x); i++)
        h = ((h*a) + x[i]) & mask;
    return h;
}

size_t hashWord(size_t word, size_t M, size_t a)
{
    return (size_t) (a*word) >> (sizeof(size_t)*CHAR_BIT - M);
}

void freeHashMapList(struct HashMapListItem *hashMapList, size_t listLength)
{
    for (size_t i = 0; i < listLength; i++) {
        free(hashMapList[i].key);
        free(hashMapList[i].value);
    }
    free(hashMapList);
}

bool hashMap__Insert(struct HashMap *hashMap2Insert2, const char *key, const char *value)
{
    size_t mask = (1 << hashMap2Insert2->bitSize) - 1;
    
    size_t insertItemIndex = hashStr(key, hashMap2Insert2->bitSize, hashMap2Insert2->a);
    struct HashMapListItem *hashMapList = hashMap2Insert2->list;
    
    while (hashMapList[insertItemIndex].initialized && strcmp(hashMapList[insertItemIndex].key, key) != 0) {
        insertItemIndex++;
        insertItemIndex &= mask;
    }

    bool retVal;
    
    if (hashMapList[insertItemIndex].initialized) {
        free(hashMapList[insertItemIndex].value);
        retVal = false;
    } else {
        hashMapList[insertItemIndex].key = calloc(strlen(key)+1, sizeof(char));
        strcpy(hashMapList[insertItemIndex].key, key);
        retVal = true;
    }
    
    
    hashMapList[insertItemIndex].value = calloc(strlen(value)+1, sizeof(char));
    hashMapList[insertItemIndex].initialized = true;
    
    strcpy(hashMapList[insertItemIndex].value, value);
    
    return retVal;
}

bool hashMap__Remove(struct HashMap *hashMap2Remove, const char *key)
{
    size_t mask = (1 << hashMap2Remove->bitSize) - 1;
    
    size_t removeItemIndex = hashStr(key, hashMap2Remove->bitSize, hashMap2Remove->a);
    struct HashMapListItem *hashMapList = hashMap2Remove->list;
    
    while (hashMapList[removeItemIndex].initialized && strcmp(hashMapList[removeItemIndex].key, key) != 0) {
        removeItemIndex++;
        removeItemIndex &= mask;
    }
    if (!hashMapList[removeItemIndex].initialized)
        return false;
    
    free(hashMapList[removeItemIndex].key);
    free(hashMapList[removeItemIndex].value);
    hashMapList[removeItemIndex].initialized = false;
    hashMapList[removeItemIndex].key = NULL;
    hashMapList[removeItemIndex].value = NULL;
    
    size_t prevMovedIndex = removeItemIndex;
    size_t newMovedIndex  = removeItemIndex + 1;
    
    if (newMovedIndex == (1 << hashMap2Remove->bitSize))
        return true;
    
    while (hashMapList[newMovedIndex].initialized) {
        if (hashStr(hashMapList[newMovedIndex].key, hashMap2Remove->bitSize, hashMap2Remove->a) < newMovedIndex) {
            hashMapList[prevMovedIndex] = hashMapList[newMovedIndex];
            prevMovedIndex = newMovedIndex;
            hashMapList[newMovedIndex].initialized = false;
            hashMapList[newMovedIndex].key = NULL;
            hashMapList[newMovedIndex].value = NULL;
        }
        newMovedIndex++;
        newMovedIndex &= mask;
    }
    
    return true;
}

void hashMap__DoubleSize(struct HashMap *hash2Double)
{
    char oldHashSize = hash2Double->bitSize;
    hash2Double->bitSize++;

    struct HashMapListItem *oldHashList = hash2Double->list;

    hash2Double->list = (struct HashMapListItem*) calloc(1 << hash2Double->bitSize, sizeof(struct HashMapListItem));
    
    for (size_t i=0; i<(1<<oldHashSize); i++) {
        if (oldHashList[i].key != NULL) {
            hashMap__Insert(hash2Double, oldHashList[i].key, oldHashList[i].value);
        }
    }

    freeHashMapList(oldHashList, 1 << oldHashSize);
}

void hashMap__HalveSize(struct HashMap *hash2Double)
{
    char oldHashSize = hash2Double->bitSize;
    hash2Double->bitSize--;

    struct HashMapListItem *oldHashList = hash2Double->list;

    hash2Double->list = (struct HashMapListItem*) calloc(1 << hash2Double->bitSize, sizeof(struct HashMapListItem));
    
    for (size_t i=0; i<(1<<oldHashSize); i++) {
        if (oldHashList[i].key != NULL) {
            hashMap__Insert(hash2Double, oldHashList[i].key, oldHashList[i].value);
        }
    }

    freeHashMapList(oldHashList, 1 << oldHashSize);
}

void hashMap__handleTooBig(struct HashMap *hash2handleBig)
{
    if (hash2handleBig->slotsFilled * 4 / (1 << hash2handleBig->bitSize) >= 3)
        hashMap__DoubleSize(hash2handleBig);
}

void hashMap__handleTooSmall(struct HashMap *hash2handleSmall)
{
    if (hash2handleSmall->bitSize <= 3)
        return;
    if (hash2handleSmall->slotsFilled * 8 / (1 << hash2handleSmall->bitSize) < 2)
        hashMap__HalveSize(hash2handleSmall);
}

bool hashMapInsert(struct HashMap *hash2insert2, const char *key, const char *value)
{
    bool retVal = hashMap__Insert(hash2insert2, key, value);
    if (retVal) {
        hash2insert2->slotsFilled++;
        hashMap__handleTooBig(hash2insert2);
    }
    return retVal;
}

bool hashMapRemove(struct HashMap *hash2remove, const char *key)
{
    bool retVal = hashMap__Remove(hash2remove, key);
    if (retVal) {
        hash2remove->slotsFilled--;
        hashMap__handleTooSmall(hash2remove);
    }
    return retVal;
}

char *hashMapGet(struct HashMap *hash2get, const char *key)
{
    size_t mask = (1 << hash2get->bitSize) - 1;
    size_t getItemIndex = hashStr(key, hash2get->bitSize, hash2get->a);
    struct HashMapListItem *hashMapList = hash2get->list;
    
    while (hashMapList[getItemIndex].initialized && strcmp(hashMapList[getItemIndex].key, key)) {
        getItemIndex++;
        getItemIndex &= mask;
    }

    if (hashMapList[getItemIndex].initialized) {
        char *valueCopy = calloc(strlen(hashMapList[getItemIndex].value)+1, sizeof(char));
        strcpy(valueCopy, hashMapList[getItemIndex].value);
        return valueCopy;
    } else return NULL;
}

const char **hashMapKeys(struct HashMap *hash2getKeys)
{
    const char **keyList = calloc(hash2getKeys->slotsFilled + 1, sizeof(char *));
    
    size_t currentKey = 0;
    for (size_t i = 0; i < (1 << hash2getKeys->bitSize); i++)
        if (hash2getKeys->list[i].initialized) {
            keyList[currentKey] = hash2getKeys->list[i].key;
            currentKey++;
        }
    
    return keyList;
}

void printHashMap(struct HashMap *hashMap2print)
{
    const char **keyList = hashMapKeys(hashMap2print);
    
    for (size_t i = 0; keyList[i] != NULL; i++) {
        char *value2Print = hashMapGet(hashMap2print, keyList[i]);
        printf("%s -> %s\n", keyList[i], value2Print);
        free(value2Print);
    }
    
    free(keyList);
}

void hashMapFree(struct HashMap *hashMap2free)
{
    freeHashMapList(hashMap2free->list, 1 << hashMap2free->bitSize);
    hashMap2free->bitSize = 0;
    hashMap2free->slotsFilled = 0;
    hashMap2free->a = 0;
    hashMap2free->list = NULL;
    free(hashMap2free);
    
}


struct HashMap *hashMapNew()
{
    struct HashMap *newHashMap = malloc(sizeof(struct HashMap));
    newHashMap->bitSize     = STARTING_BITS;
    newHashMap->slotsFilled = 0;
    newHashMap->a           = randomsize_t();
    newHashMap->list        = calloc(1 << STARTING_BITS, sizeof(struct HashMapListItem));
    return newHashMap;
}

