#include "headers/run/run.h"
#include "headers/file/file.h"
#include "headers/hash/hashstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void run(char** playableFile) {
    /*Read File into memory*/
    hashSetStringNoTable("FUNCTION");
    //hashSetStringNoTable("string");
    int *integerArr = (void*)0;
    unsigned int* integerVarNames =(void*)0;
    unsigned int maxInts = 10;
    integerArr = (int*)calloc(maxInts, sizeof(integerArr[0]));
    integerVarNames = (unsigned int*)calloc(maxInts, sizeof(integerVarNames[0]));



    int *aliasValArr = (void*)0;
    int *aliasTypeArr = (void*)0;
    unsigned int* aliasArrHash =(void*)0;
    unsigned int maxAlias = 10;
    aliasValArr = (int*)calloc(maxAlias, sizeof(aliasValArr[0]));
    aliasTypeArr = (int*)calloc(maxAlias, sizeof(aliasTypeArr[0]));
    aliasArrHash = (unsigned int*)calloc(maxAlias, sizeof(aliasArrHash[0]));



    char* playableFileContents = (void*)0;
    if(fileRead(playableFile[0], &playableFileContents, 1) != 0) {
        /*Return if failed*/
        return;
    }
    /*Make sure file ends with a newline to avoid crashing*/
    playableFileContents[strlen(playableFileContents)] = '\n';
    /*Index set*/
    char* filePointer = playableFileContents;
    /*Check if first character is a comment*/
    if(filePointer[0] == ';') {
        /*Go to newline*/
        filePointer = strchr(filePointer, '\n');
    }
    while(filePointer[0]) {
        /*Skip over whitespace*/
        switch(filePointer[0]){
            case ' ':
            case '\t':
            case '\n':
        filePointer += strcspn(filePointer, "; \t\n\0");
        ++filePointer;
        break;
        default:{
            break;
        }
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
                    case 572:{
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
                    case 688:{
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
                    case 858:{
                        /*setAlias*/
                        filePointer[0] = charStorage;
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
                            case 650:{
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

                    }
                    case 684:{
                        /*string*/
                        break;
                    }
                    
                    case 337:
                    /*int*/
                    case 778:{
                        /*integer*/
                        filePointer[0] = charStorage;
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

    free(playableFileContents);
    return;
}