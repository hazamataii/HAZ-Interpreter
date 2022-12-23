#include "headers/run/run.h"
#include "headers/file/file.h"
#include "headers/hash/hashstr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compile(char** playableFile) {

    unsigned int maxInts = 10;
    int *integerArr = (void*)0;
    integerArr = (int*)calloc(maxInts, sizeof(integerArr[0]));
    unsigned int* integerVarNames =(void*)0;
    
    unsigned int currentInts = 0;
    //integerArr = (int*)calloc(maxInts, sizeof(integerArr[0]));
    integerVarNames = (unsigned int*)calloc(maxInts, sizeof(integerVarNames[0]));



    unsigned int *aliasValArr = (void*)0;
    int *aliasTypeArr = (void*)0;
    unsigned int* aliasArrHash =(void*)0;
    unsigned int maxAlias = 10;
    aliasValArr = (unsigned int*)calloc(maxAlias, sizeof(aliasValArr[0]));
    aliasTypeArr = (int*)calloc(maxAlias, sizeof(aliasTypeArr[0]));
    aliasArrHash = (unsigned int*)calloc(maxAlias, sizeof(aliasArrHash[0]));
    unsigned int currAlias = 0;

    /*Read File into memory*/
    char* playableFileContents = (void*)0;
    if(fileRead(playableFile[0], &playableFileContents, 1) != 0) {
        /*Return if failed*/
        return;
    }
    /*Make sure file ends with a newline to avoid crashing*/
    playableFileContents[strlen(playableFileContents)] = '\n';
    /*Set OutputFile size to InputFile size*/
    unsigned long long curFileSizeMax = strlen(playableFileContents);
    char* outputFileContents = (void*)0;
    outputFileContents = (char*)calloc(curFileSizeMax+31, sizeof(outputFileContents[0]));
    register unsigned long long int i = 32;
    /*Header*/
    outputFileContents[0] = 0x7F;
    outputFileContents[1] = 'H';
    outputFileContents[2] = 'A';
    outputFileContents[3] = 'Z';
    outputFileContents[4] = 'L';
    outputFileContents[5] = 'B';
    outputFileContents[6] = 'L';
    /*Major Ver*/
    outputFileContents[7] = 0x00;
    outputFileContents[8] = 0x00;
    outputFileContents[9] = 0x00;
    outputFileContents[10] = 0x00;
    outputFileContents[11] = 0x00;
    outputFileContents[12] = 0x00;
    outputFileContents[13] = 0x00;
    outputFileContents[14] = 0x00;
    /*Minor Ver*/
    outputFileContents[15] = 0x00;
    outputFileContents[16] = 0x00;
    outputFileContents[17] = 0x00;
    outputFileContents[18] = 0x00;
    outputFileContents[19] = 0x00;
    outputFileContents[20] = 0x00;
    outputFileContents[21] = 0x00;
    outputFileContents[22] = 0x00;
    /*Redition Ver*/
    outputFileContents[23] = 0x00;
    outputFileContents[24] = 0x00;
    outputFileContents[25] = 0x00;
    outputFileContents[26] = 0x00;
    outputFileContents[27] = 0x00;
    outputFileContents[28] = 0x00;
    outputFileContents[29] = 0x00;
    outputFileContents[30] = 0x00;
    /*Build Letter*/
    outputFileContents[31] = 'I';
    /*Index set*/
    char* filePointer = playableFileContents;
    /*Check if first character is a comment*/
    if(filePointer[0] == ';') {
        /*Go to newline*/
        filePointer = strchr(filePointer, '\n');
    }
    while(filePointer[0]) {
        /*Skip over whitespace*/
        filePointer += strcspn(filePointer, "; \t\n\0");
        ++filePointer;
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
                switch(hashCheckStringValueNoTable(tmpToken)) {
                    case 572:{
                        /*print*/
                        outputFileContents[i] = 0x01;
                        ++i;

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
                                outputFileContents[i] = 0;
                                ++i;
                                memcpy(&outputFileContents[i], tmpToken, strlen(tmpToken));
                                i += strlen(tmpToken);
                                filePointer[0] = '"';
                                break;
                            }
                            default:{
                                tmpToken = filePointer;
                                filePointer += strcspn(filePointer, " \t\n)");
                                charStorage = filePointer[0];
                                filePointer[0] = 0;
                                outputFileContents[i] = 1;
                                ++i;
                               // printf("%i", integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)]);
                                filePointer[0] = charStorage;
                                break;
                            }
                        }
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');

                        memcpy(&outputFileContents[i], tmpToken, strlen(tmpToken));
                        i += strlen(tmpToken);
                        outputFileContents[i] = 0;
                        ++i;
                        filePointer[0] = '"';
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 688:{
                        /*printn*/
                        outputFileContents[i] = 0x01;
                        ++i;
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '(');
                        filePointer = strchr(filePointer, '"');
                        ++filePointer;
                        tmpToken = filePointer;
                        filePointer = strchr(filePointer, '"');
                        filePointer[0] = 0;
                        memcpy(&outputFileContents[i], tmpToken, strlen(tmpToken));
                        i += strlen(tmpToken);
                        outputFileContents[i] = '\n';
                        ++i;
                        outputFileContents[i] = 0x00;
                        ++i;
                        filePointer[0] = '"';
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 684:{
                        /*string*/
                    }
                    case 858:{
                        /*setAlias*/
                        filePointer[0] = charStorage;
                        /*Resize*/
                        if(currAlias == (maxAlias-1)){
                        unsigned int const Old = maxAlias;
                        maxAlias+= 10;
                        aliasTypeArr = (int*)realloc(aliasTypeArr,(sizeof(aliasTypeArr[0])*maxAlias));
                        aliasValArr = (unsigned int*)realloc(aliasValArr,(sizeof(aliasTypeArr[0])*maxAlias));
                        aliasArrHash = (unsigned int*)realloc(aliasArrHash, (sizeof(aliasArrHash[0])*maxAlias));
                        memset(&aliasArrHash[Old], 0, (maxAlias-1));
                        }
                        ++currAlias;
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
                    default:{
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                }
                break;
            }
        } 
    }
    outputFileContents[i] = 0;
    char* outName = (void*)0;
    outName = (char*)calloc((strlen(playableFile[0])+2), sizeof(outName[0]));
    memcpy(outName, playableFile[0], strlen(playableFile[0]));
    outName[strlen(playableFile[0])] = 'b';
    fileWrite(outName, outputFileContents, (i+1));
    free(playableFileContents);
    return;
}