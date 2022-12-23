#include "headers/run/run.h"
#include "headers/file/file.h"
#include "headers/hash/hashstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void run(char** playableFile) {
    /*Read File into memory*/
    /*hashSetStringNoTable("int");
    hashSetStringNoTable("integer");
    hashSetStringNoTable("print");
    hashSetStringNoTable("printn");
    hashSetStringNoTable("setAlias");
    hashSetStringNoTable("FUNCTION");
    hashSetStringNoTable("playFile");*/

    /*File Pointers*/
    unsigned int maxFiles = 10;
    unsigned int curFile = 0;
    char** posPointer = (void*)0;
    char** fileStorage = (void*)0;
    posPointer = (char**)calloc(maxFiles, sizeof(posPointer[0]));
    fileStorage = (char**)calloc(maxFiles, sizeof(fileStorage[0]));

    /*Integer Setup*/
    unsigned int maxInts = 10;
    int *integerArr = (void*)0;
    integerArr = (int*)calloc(maxInts, sizeof(integerArr[0]));
    unsigned int* integerVarNames =(void*)0;
    unsigned int currentInts = 0;
    integerVarNames = (unsigned int*)calloc(maxInts, sizeof(integerVarNames[0]));

    /*Alias setup*/
    unsigned int *aliasValArr = (void*)0;
    int *aliasTypeArr = (void*)0;
    unsigned int* aliasArrHash =(void*)0;
    unsigned int maxAlias = 10;
    aliasValArr = (unsigned int*)calloc(maxAlias, sizeof(aliasValArr[0]));
    aliasTypeArr = (int*)calloc(maxAlias, sizeof(aliasTypeArr[0]));
    aliasArrHash = (unsigned int*)calloc(maxAlias, sizeof(aliasArrHash[0]));
    unsigned int currAlias = 0;


    /*char* playableFileContents = (void*)0;*/
    if(fileRead(playableFile[0], &fileStorage[0], 1) != 0) {
        /*Return if failed*/
        return;
    }
    /*Make sure file ends with a newline to avoid crashing*/
    fileStorage[0][strlen(fileStorage[0])] = '\n';
    /*Index set*/
    char* filePointer = fileStorage[0];
    /*Check if first character is a comment*/
    //if(filePointer[0] == ';') {
        /*Go to newline*/
    //    filePointer = strchr(filePointer, '\n');
    //}
    TOPOFRUN:
    while(filePointer[0]) {
        /*Skip over whitespace*/
        while(filePointer[0] == ' ' || filePointer[0] == '\n'  || filePointer[0] == '\t') {
            ++filePointer;
        }
        switch(filePointer[0]) {
            case 0:{
                /*Stop reading here*/
                break;
            }
            case '\n':{
                ++filePointer;
                break;
            }
            case ';':{
                /*Comment*/
                filePointer = strchr(filePointer, '\n');
                break;
            }
            default:{
                /*Get token*/
                char* tmpToken = filePointer;
                filePointer += strcspn(filePointer, " (");
                register char charStorage = filePointer[0];
                filePointer[0] = 0;
                unsigned int tokenHashVal = hashCheckStringValueNoTable(tmpToken);
                HASHLABELTOP:
                switch(tokenHashVal) {
                    case 1405481478:{
                        /*print*/
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '(');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        switch(filePointer[0]) {
                            case '"':{
                                ++filePointer;
                                tmpToken = filePointer;
                                filePointer = strchr(filePointer, '"');
                                filePointer[0] = 0;
                                printf("%s", tmpToken);
                                filePointer[0] = '"';
                                break;
                            }
                            default:{
                                tmpToken = filePointer;
                                filePointer += strcspn(filePointer, " \t\n)");
                                charStorage = filePointer[0];
                                filePointer[0] = 0;
                                printf("%i", integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)]);
                                filePointer[0] = charStorage;
                                break;
                            }
                        }
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 1041173394:{
                        /*printn*/
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '(');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        switch(filePointer[0]) {
                            case '"':{
                                ++filePointer;
                                tmpToken = filePointer;
                                filePointer = strchr(filePointer, '"');
                                filePointer[0] = 0;
                                printf("%s\n", tmpToken);
                                filePointer[0] = '"';
                                break;
                            }
                            default:{
                                tmpToken = filePointer;
                                filePointer += strcspn(filePointer, " \t\n)");
                                charStorage = filePointer[0];
                                filePointer[0] = 0;
                                printf("%i\n", integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)]);
                                filePointer[0] = charStorage;
                                break;
                            }
                        }
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 1035894603:{
                        /*setAlias*/
                        filePointer[0] = charStorage;
                        /*Resize*/
                        if(currAlias == maxAlias){
                        unsigned int const Old = maxAlias;
                        maxAlias+= 10;
                        aliasTypeArr = (int*)realloc(aliasTypeArr,(sizeof(aliasTypeArr[0])*maxAlias));
                        aliasValArr = (unsigned int*)realloc(aliasValArr,(sizeof(aliasTypeArr[0])*maxAlias));
                        aliasArrHash = (unsigned int*)realloc(aliasArrHash, (sizeof(aliasArrHash[0])*maxAlias));
                        memset(&aliasArrHash[Old], 0, (maxAlias-1));
                        }
                        filePointer = strchr(filePointer, '(');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        tmpToken = filePointer;
                        filePointer += strcspn(filePointer, " ,");
                        charStorage = filePointer[0];
                        filePointer[0] = 0;
                        char Type = 0;
                        switch(hashCheckStringValueNoTable(tmpToken)) {
                            case 1347283628:{
                                /*FUNCTION*/
                                Type = 1;
                                break;
                            }
                            default:{
                                break;
                            }
                        }

                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, ',');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        tmpToken = filePointer;
                        filePointer += strcspn(filePointer, " ,");
                        charStorage = filePointer[0];
                        filePointer[0] = 0;
                        unsigned int const tokenHash = hashCheckStringValueNoTable(tmpToken);

                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, ',');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        tmpToken = filePointer;
                        filePointer += strcspn(filePointer, " )");
                        charStorage = filePointer[0];
                        filePointer[0] = 0;
                        hashSetString(tmpToken, &aliasArrHash, maxAlias);
                        unsigned int const Pos = hashCheckStringPos(tmpToken, aliasArrHash, maxAlias);
                        aliasTypeArr[Pos] = Type;
                        aliasValArr[Pos] = tokenHash;
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                        ++currAlias;
                        break;
                    }
                    case 684:{
                        /*string*/
                        break;
                    }
                    
                    case 556453026:
                    /*int*/
                    case 3305686986:{
                        /*integer*/
                        filePointer[0] = charStorage;
                        /*reallocate if max size*/
                        if(currentInts == (maxInts)){
                        unsigned int const Old = maxInts;
                        maxInts+= 10;
                        if((integerArr = (int*)realloc(integerArr,(sizeof(integerArr[0])*maxInts))) == (void*)0) {
                        }
                        integerVarNames = (unsigned int*)realloc(integerVarNames, (sizeof(integerVarNames[0])*maxInts));
                        memset(&integerVarNames[Old], 0, (maxInts-1));
                        }
                        filePointer = strchr(filePointer, ' ');
                        ++filePointer;
                        tmpToken = filePointer;
                        filePointer += strcspn(filePointer, " =");
                        charStorage = filePointer[0];
                        filePointer[0] = 0;
                        hashSetString(tmpToken, &integerVarNames, maxInts);
                        register unsigned int const pos = hashCheckStringPos(tmpToken, integerVarNames, maxInts);
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '=');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        integerArr[pos] = atoi(filePointer);
                        filePointer = strchr(filePointer, '\n');
                        ++currentInts;
                        break;
                    }
                    case 4007848917:{
                        /*playFile*/
                        filePointer[0] = charStorage;
                        ++curFile;
                        if(curFile == maxFiles){
                        unsigned int const Old = maxFiles;
                        maxFiles+= 10;
                        posPointer = (char**)realloc(aliasTypeArr,(sizeof(posPointer[0])*maxFiles));
                        fileStorage = (char**)realloc(aliasValArr,(sizeof(fileStorage[0])*maxFiles));
                        }
                        filePointer = strchr(filePointer, '(');
                        filePointer = strchr(filePointer, '"');
                        ++filePointer;
                        tmpToken = filePointer;
                        filePointer = strchr(filePointer, '"');
                        charStorage = filePointer[0];
                        filePointer[0] = 0;

                        fileRead(tmpToken, &fileStorage[curFile], 1);
                        filePointer[0] = charStorage;
                        /*Make sure file ends with a newline to avoid crashing*/
                        fileStorage[curFile][strlen(fileStorage[curFile])] = '\n';
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                       // printf("File:\n%u\n", curFile);
                        posPointer[(curFile-1)] = filePointer;
                        filePointer = fileStorage[curFile];
                        
                        break;
                    }
                    default:{
                        unsigned int const Pos = hashCheckStringPos(tmpToken, aliasArrHash, maxAlias);
                        if(Pos == maxAlias){
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '\n');
                        break;
                        } else {
                            tokenHashVal = aliasValArr[Pos];
                            goto HASHLABELTOP;
                        }
                        break;
                    }
                }
                break;
            }
        } 
    }

    //--curFile;
    free(fileStorage[curFile]);
    //printf("%u\n", curFile);
    --curFile;
    if(curFile != 0xffffffff) {
        filePointer = posPointer[curFile];
        goto TOPOFRUN;
    }
    return;
}