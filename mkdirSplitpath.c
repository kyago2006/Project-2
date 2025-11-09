

#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
    //checks for path
    if (pathName[0] == '/') {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    //creates needed vars
    char baseName[100];
    char dirName[200];
    struct NODE* parentNode = splitPath(pathName, baseName, dirName);
    if (parentNode == NULL) {
        return;
    }
    //create new node
    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    strcpy(newNode->name, baseName);
    newNode->fileType = 'D';
    newNode->parentPtr = parentNode;
    newNode->siblingPtr = NULL;
    newNode->childPtr = NULL;

    //check for alr filename
    if(parentNode->childPtr != NULL) {
    for (struct NODE* cNode = parentNode->childPtr; cNode != NULL; cNode = cNode->siblingPtr)
    {
        if (strcmp(baseName, cNode->name) == 0) {
            printf("MKDIR ERROR: directory %s already exists\n", pathName);
            return;
        }
        if (cNode->siblingPtr == NULL) {
            cNode->siblingPtr = newNode;
            break;
        }
    }
}
else {
    parentNode->childPtr = newNode;
}
    
    //sucess
    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);

    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HER

    char* token;
    char* lastTok = NULL;

    struct NODE* node = NULL;\
    if (pathName[0] == '/') {
        node = root;
    }
    else {
        node = cwd;
    }
    char t[200];
    strcpy(t, pathName);
    
    token = strtok(t, "/");
    while (token != NULL) {
        if (lastTok != NULL) {
            struct NODE* sib = node->childPtr;
            while (sib != NULL) {
                if (sib->fileType == 'D' && strcmp(sib->name, lastTok) == 0) {
                    node = sib;
                    break;
                }
                sib = sib->siblingPtr;
            }
            if (sib == NULL) {
                printf("ERROR: directory %s does not exist\n", lastTok);
                return NULL;
            }
            strcat(dirName, "/");
            strcat(dirName, lastTok);
        }
        lastTok = token;
        token = strtok(NULL, "/");
    }
    if (lastTok != NULL) {
        strcpy(baseName, lastTok);
    }
    else {
        strcpy(dirName, "/");
        strcpy(baseName, "");
    }
    

    return node;
}
