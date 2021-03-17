#include "io-fs-path.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *__curly_get_home_dir() {
    return getenv("HOME");
}

char getPathRootType(char rootChar) {
    switch (rootChar) {
        case('/'):
        case('\\'):
            return 'R';
            break;

        case('~'):
            return 'H';
            break;

        case('A'):
        case('B'):
        case('C'):
        case('D'):
        case('E'):
        case('F'):
        case('G'):
        case('H'):
        case('I'):
        case('J'):
        case('K'):
        case('L'):
        case('M'):
        case('N'):
        case('O'):
        case('P'):
        case('Q'):
        case('R'):
        case('S'):
        case('T'):
        case('U'):
        case('V'):
        case('W'):
        case('X'):
        case('Y'):
        case('Z'):
            return 'D';
            break;

        default:
            return '\0';
            break;
    }
}


int getPathStrLen(Path *pathToString) {
    int totalStringLength = 0;

    PathNode* current = pathToString->nextNode;

    switch (getPathRootType(pathToString->root)) {
        case('R'):
            break;

        case('H'):
            totalStringLength += strlen(__curly_get_home_dir());
            totalStringLength -= current == NULL;
            break;

        case('D'):
            totalStringLength += 2;
            break;

        default:
            totalStringLength--;
            break;
    }

    if (current == NULL) {
        totalStringLength++;
    }

    while (current != NULL) {
        totalStringLength++;
        totalStringLength += strlen(current->nodeContents);
        current = current->nextNode;
    }

    return totalStringLength;
}

char *__curly_path_to_string(Path *pathToString) {
    int strLen = getPathStrLen(pathToString);
    char *pathString = (char*) calloc(strLen + 1, sizeof(char));

    PathNode *current = pathToString->nextNode;
    int currIndex = 0;

    char *homeDir = __curly_get_home_dir();

    switch (getPathRootType(pathToString->root)) {
        case('R'):
            pathString[0] = pathSeperator;
            currIndex ++;
            break;

        case('H'):
            strcpy(pathString, homeDir);
            currIndex += strlen(homeDir);

            pathString[currIndex] = pathSeperator;
            currIndex++;
            break;

        case('D'):
            pathString[0] = pathToString->root;
            strcpy(pathString + sizeof(char), ":\\");
            currIndex += 3;
            break;

        default:
            break;
    }

    while (current != NULL) {
        strcpy(pathString + currIndex * sizeof(char), current->nodeContents);
        currIndex += strlen(current->nodeContents);

        pathString[currIndex] = pathSeperator;
        currIndex++;

        current = current->nextNode;
    }

    pathString[strLen] = '\0';
    return pathString;
}


Path *__curly_string_to_path(char *stringToPath) {
    char *relPathPos = NULL;
    char rootChar = '\0';

    Path *outputPath = calloc(1, sizeof(Path));

    PathNode **currPathNode = &outputPath->nextNode;

    if (pathSeperator == '\\' && stringToPath[1] == ':') {
        relPathPos = stringToPath + 3 * sizeof(char);
    }

    if (stringToPath[0] == pathSeperator) {
        relPathPos = stringToPath + sizeof(char);
    }

    if (stringToPath[0] == '~') {
        relPathPos = stringToPath + sizeof(char);
        if (stringToPath[1] != '\0') {
            relPathPos += sizeof(char);
        }
    }


    if (relPathPos != NULL) {
        switch (getPathRootType(stringToPath[0])) {
            case('R'):
                rootChar = pathSeperator;
                break;

            case('H'):
                rootChar = '~';
                break;

            case('D'):
                rootChar = stringToPath[0];
                break;

            default:
                return NULL;
                break;
        }
    } else relPathPos = stringToPath;

    outputPath->root = rootChar;

    while(strlen(relPathPos) != 0) {
        *currPathNode = calloc(1, sizeof(PathNode));

        char *nextSep = strchr(relPathPos, pathSeperator);
        int nodeContentsSize;

        if (nextSep == NULL) 
            nodeContentsSize = strlen(relPathPos);
        else
            nodeContentsSize = nextSep - relPathPos;

        (*currPathNode)->nodeContents = calloc(nodeContentsSize + 1, sizeof(char));
        strncpy((*currPathNode)->nodeContents, relPathPos, nodeContentsSize);

        
        relPathPos += sizeof(char) * nodeContentsSize;
        if (nextSep != NULL)
            relPathPos += sizeof(char);
        else if (relPathPos[0] == pathSeperator && relPathPos[1] == '\0')
            relPathPos += 1;

        currPathNode = &(*currPathNode)->nextNode;
    }

    return outputPath;
}



void __curly_free_path(Path *pathToFree) {
    PathNode *currentNode = pathToFree->nextNode;
    PathNode *cN1 = NULL;

    while (currentNode != NULL) {
        free(currentNode->nodeContents);
        cN1 = currentNode;
        currentNode = currentNode->nextNode;
        free(cN1);
    }

    free(pathToFree);
}


Path *__curly_copy_path(Path *pathToCopy) {
    Path *outputPath = calloc(1, sizeof(Path));
    outputPath->root = pathToCopy->root;

    PathNode **currentDest = &outputPath->nextNode;
    PathNode *currentSrc = pathToCopy->nextNode;

    while (currentSrc != NULL) {
        *currentDest = calloc(1, sizeof(PathNode));

        (*currentDest)->nodeContents = calloc(strlen(currentSrc->nodeContents) + 1, sizeof(char));
        strcpy((*currentDest)->nodeContents, currentSrc->nodeContents);

        currentSrc = currentSrc->nextNode;
        currentDest = &(*currentDest)->nextNode;
    }

    return outputPath;
}
