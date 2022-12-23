#include "headers/run/run.h"
#include "headers/file/file.h"
#include "headers/hash/hashstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void run(char** playableFile) {

    /*Get Hsh values for keywords*/
    /*hashSetStringNoTable("int");
    hashSetStringNoTable("integer");
    hashSetStringNoTable("print");
    hashSetStringNoTable("printn");
    hashSetStringNoTable("setAlias");
    hashSetStringNoTable("FUNCTION");
    hashSetStringNoTable("playFile");
    hashSetStringNoTable("getInput");
    hashSetStringNoTable("if");*/
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

    /*Read File into memory*/
    if(fileRead(playableFile[0], &fileStorage[0], 1) != 0) {
        /*Return if failed*/
        return;
    }
    /*Make sure file ends with a newline to avoid crashing*/
    fileStorage[0][strlen(fileStorage[0])] = '\n';
    /*Index set*/
    char* filePointer = fileStorage[0];
    int ifFailed = 0;
    //int ifSuccess = 0;
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
            case '}':{
                if(ifFailed != 0){
                --ifFailed;
                }
                ++filePointer;
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
                        if(ifFailed == 0){
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
                        }
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 1041173394:{
                        /*printn*/
                        filePointer[0] = charStorage;
                        if(ifFailed == 0){
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
                        }
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 1868075329:{
                        /*getInput*/
                        filePointer[0] = charStorage;
                        if(ifFailed == 0){
                        filePointer = strchr(filePointer, '(');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        tmpToken = filePointer;
                        filePointer += strcspn(filePointer, " )");
                        charStorage = filePointer[0];
                        filePointer[0] = 0;
                        scanf("%d", &integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)]);
                        filePointer[0] = charStorage;
                        }
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 1035894603:{
                        /*setAlias*/
                        filePointer[0] = charStorage;
                        if(ifFailed == 0){
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
                        ++currAlias;
                        }
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 684:{
                        /*string*/
                        break;
                    }
                    case 3200026375:{
                        /*if*/
                        filePointer[0] = charStorage;
                        int Res = 0;
                        if(ifFailed == 0){
                        filePointer = strchr(filePointer, '(');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        int Value1 = 0;
                        if(filePointer[0] >= '0' && filePointer[0] <= '9') {
                            Value1 = atoi(filePointer);
                        } else {
                            tmpToken = filePointer;
                            filePointer += strcspn(filePointer, " \n=<>!");
                            charStorage = filePointer[0];
                            filePointer[0] = 0;
                            Value1 = integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)];
                            filePointer[0] = charStorage;
                        }
                        filePointer += strcspn(filePointer, "=<>!");
                        char First = filePointer[0];
                        char Second = filePointer[1];
                        filePointer += 2;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        int Value2 = 0;
                        if(filePointer[0] >= '0' && filePointer[0] <= '9') {
                            Value2 = atoi(filePointer);
                        } else {
                            tmpToken = filePointer;
                            filePointer += strcspn(filePointer, " \n)");
                            charStorage = filePointer[0];
                            filePointer[0] = 0;
                            Value2 = integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)];
                            filePointer[0] = charStorage;
                        }
                        
                        if(Second == '=') {
                            Res = (((First == '=')*(Value1 == Value2))+((First == '<')*(Value1 <= Value2)) + ((First == '>')*(Value1 >= Value2))+ ((First == '!')*(Value1 != Value2)));
                        }
                        switch(Res) {
                            case 0:{
                                Res = 1;
                                break;
                            }
                            case 1:{
                                Res = 0;
                                break;
                            }
                            default:{
                                break;
                            }
                        }
                        ifFailed += Res;
                        filePointer = strchr(filePointer, ')');
                        }
                        if(Res == 0){
                        ifFailed += (ifFailed > 0);
                        }
                        filePointer = strchr(filePointer, ')');
                        filePointer = strchr(filePointer, '{');
                        ++filePointer;
                        break;
                    }
                    case 556453026:
                    /*int*/
                    case 3305686986:{
                        /*integer*/
                        filePointer[0] = charStorage;
                        /*reallocate if max size*/
                        if(ifFailed == 0){
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
                        ++currentInts;
                        }
                        filePointer = strchr(filePointer, '\n');
                        break;
                    }
                    case 4007848917:{
                        /*playFile*/
                        filePointer[0] = charStorage;
                        if(ifFailed == 0){
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
                        }
                        filePointer = strchr(filePointer, '\n');
                        if(ifFailed == 0) {
                            posPointer[(curFile-1)] = filePointer;
                            filePointer = fileStorage[curFile];
                        }
                        
                        break;
                    }
                    default:{
                        if(ifFailed == 0){
                        unsigned int Pos = hashCheckStringPos(tmpToken, integerVarNames, maxInts);
                        //printf("POS:%u, max:%u", Pos, maxInts);
                        if(Pos < maxInts) {
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '=');
                        ++filePointer;
                        while(filePointer[0] == ' ') {
                            ++filePointer;
                        }
                        if(filePointer[0] >= '0' && filePointer[0] <= '9') {
                            integerArr[Pos] = atoi(filePointer);
                        } else {
                            tmpToken = filePointer;
                            filePointer += strcspn(filePointer, " \n");
                            charStorage = filePointer[0];
                            filePointer[0] = 0;
                            integerArr[Pos] = integerArr[hashCheckStringPos(tmpToken, integerVarNames, maxInts)];
                            filePointer[0] = charStorage;
                        }
                        filePointer = strchr(filePointer, '\n');
                        } else {
                        Pos = hashCheckStringPos(tmpToken, aliasArrHash, maxAlias);
                        if(Pos == maxAlias){
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '\n');
                        break;
                        } else {
                            tokenHashVal = aliasValArr[Pos];
                            goto HASHLABELTOP;
                        }
                        }
                        } else {
                        filePointer[0] = charStorage;
                        filePointer = strchr(filePointer, '\n');
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