#include "headers/run/bytecode/runByte.h"
#include "headers/file/file.h"
//#include "headers/hash/hashstr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void runByte(char** playableFile) {
    /*Read File into memory*/
    
    char* playableFileContents = (void*)0;
    if(fileRead(playableFile[0], &playableFileContents, 0) != 0) {
        /*Return if failed*/
        return;
    }
    /*Index set*/
    char* filePointer = playableFileContents;
    if(filePointer[0] == 0x7f && filePointer[1] == 'H' && filePointer[2] == 'A' && filePointer[3] == 'Z' && filePointer[4] == 'L' && filePointer[5] == 'B') {

    } else {
        printf("INVALID FILE\n");
        return;
    }
    char Endienness = filePointer[6];
    unsigned long long int const *MajorVer = (unsigned long long int const*)&filePointer[7];
    unsigned long long int const *MinorVer = (unsigned long long int const*)&filePointer[15];
    unsigned long long int const *ReditionVer = (unsigned long long int const*)&filePointer[23];
    char const BuildLetter = filePointer[31];

    if(MajorVer[0] != 0 || MinorVer[0] != 0 || ReditionVer[0] != 0 || BuildLetter != 'I') {
        printf("Incorrect version, may be undesirable\n");
    }
    filePointer += 32;
    while(filePointer[0]) {
        /*Skip over whitespace*/
        switch(filePointer[0]) {
            case 1:{
                /*print*/
                ++filePointer;
                printf("%s", filePointer);
                filePointer += (strlen(filePointer)+1);
                break;
            }
            
            default:{
                /*Invalid*/
                ++filePointer;
                break;
            }
        } 
    }

    free(playableFileContents);
    return;
}