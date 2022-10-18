#include "token.h"


typedef struct CMDToken{
    i8 CommandNumber;
    struct CMDToken* next;
}CMDToken;
typedef struct IntName{
    i8* IntegerName;
    i32 Default;
    struct IntName* next;
}IntName;
typedef struct CharName{
    i8* CharacterName;
    i8  Default;
    struct CharName* next;
}CharName;
#include <stdlib.h>
#include <string.h>

CMDToken* commandsTokenList = (void*)0;
IntName* IntegerTokenList = (void*)0;
CharName* CharacterTokenList = (void*)0;
u64 IntegersTotal = 0, CharacterTotal = 0;

void Tokenizer(const i8* src, const u64 size) {
    u64 i = 0;
    commandsTokenList = (CMDToken*)calloc(1, sizeof(CMDToken));
    CMDToken* cmdTokenPTR = commandsTokenList;
    IntegerTokenList = (IntName*)calloc(1, sizeof(IntName));
    IntName* intNameTKNPTR = IntegerTokenList;
    u64 line = 0, character = 0;
    CharacterTokenList = (CharName*)calloc(1, sizeof(CharName));
    CharName* CharNameTknPtr = CharacterTokenList;
    while(i <= size && src[i] != 0) {
        while((src[i] == ' ' || src[i] == '\n' || src[i] == ';') && (i <= size && src[i] != 0)) {
        if(src[i] == ';') {
            ++i;
            ++character;
            while(src[i] != ';') {
                if(src[i] == '\n') {
                    ++line;
                    character = 0;
                }
                ++character;
                ++i;
            }
        }
        if(src[i] == '\n') {
            ++line;
            character = 0;
        }
        ++i;
        ++character;
        }
        if(i <= size && src[i] != 0) {
            switch(src[i]) {
                case 'L':{
                    if(*((i64*)&src[i]) == 0x4354584544414F4C) {
                        i += 3;
                        cmdTokenPTR->CommandNumber = 3;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                    }
                    break;
                }

                case 'c':{
                    if(*((i32*)&src[i]) == 0x72616863) {
                        i += 4;
                        character += 4;
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] == '\n' || src[i] == 0) {
                            break;
                        }
                        while(src[i] == ' ') {
                            ++i;
                            ++character;
                        }
                        u64 start = i;
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != ';' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        cmdTokenPTR->CommandNumber = 2;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        CharNameTknPtr->CharacterName = (char*)calloc(((i-start) + 1), sizeof(char));
                        strncpy(CharNameTknPtr->CharacterName, &src[start], (i-start));
                        CharNameTknPtr->next = (CharName*)calloc(1, sizeof(CharName));
                        ++CharacterTotal;
                        while(src[i] != '\n' && src[i] != 0 && src[i] != '=') {
                            ++i;
                        }
                        if(src[i] == '\n') {
                            CharNameTknPtr->Default = 0;
                            while(src[i] != '\n' && src[i] != 0) {
                                ++i;
                            }
                            CharNameTknPtr = CharNameTknPtr->next;
                            break;
                        }
                        ++i;
                        while(src[i] == ' ') {
                            ++i;
                        }
                        if(src[i] == '\'') {
                            CharNameTknPtr->Default = src[i+1];
                            if(src[i+2] != '\'') {
                            }
                        } else {
                            CharNameTknPtr->Default = atoi(&src[i]);
                        }
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                        CharNameTknPtr = CharNameTknPtr->next;
                    }
                    break;
                }
                
                case 'i':{
                    if(*((i16*)&src[i+1]) == 0x746e) {
                        i += 3;
                        character += 3;
                        if(src[i] != ' ') {
                            while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] == '\n' || src[i] == 0) {
                            break;
                        }
                        while(src[i] == ' ') {
                            ++i;
                            ++character;
                        }
                        u64 start = i;
                        while(src[i] != '=' && src[i] != ' ' && src[i] != '\n' && src[i] != ';' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] != ' ' && src[i] != '=' && src[i] != '\n' ) {
                            while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        if((i - start) <= 0) {
                             while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        cmdTokenPTR->CommandNumber = 1;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        intNameTKNPTR->IntegerName = (char*)calloc(((i-start) + 1), sizeof(char));
                        intNameTKNPTR->next = (IntName*)calloc(1, sizeof(IntName));
                        ++IntegersTotal;
                        if((i - start) == 1) {
                            intNameTKNPTR->IntegerName[0] = src[start];
                        } else {
                        strncpy(intNameTKNPTR->IntegerName, &src[start], (i-start));
                        }
                        while(src[i] != '\n' && src[i] != 0 && src[i] != '=') {
                            ++i;
                        }
                        if(src[i] == '\n') {
                            intNameTKNPTR->Default = 0;
                            intNameTKNPTR = intNameTKNPTR->next;
                            break;
                        }
                        ++i;
                        while(src[i] == ' ') {
                            ++i;
                        }
                        intNameTKNPTR->Default = atoi(&src[i]);
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                        intNameTKNPTR = intNameTKNPTR->next;
                    }
                    break;
                }
                defalt:{
                    break;
                }
            }
            if(src[i] == '\n') {
            ++line;
            character = 0;
        }
            ++i;
        }
    }


    return;
}

#include <stdio.h>
void TokenizerDebug(const i8* src, const u64 size) {
    u64 i = 0;
    commandsTokenList = (CMDToken*)calloc(1, sizeof(CMDToken));
    CMDToken* cmdTokenPTR = commandsTokenList;
    IntegerTokenList = (IntName*)calloc(1, sizeof(IntName));
    IntName* intNameTKNPTR = IntegerTokenList;
    u64 line = 0, character = 0;
    CharacterTokenList = (CharName*)calloc(1, sizeof(CharName));
    CharName* CharNameTknPtr = CharacterTokenList;
    while(i <= size && src[i] != 0) {
        while((src[i] == ' ' || src[i] == '\n' || src[i] == ';') && (i <= size && src[i] != 0)) {
        if(src[i] == ';') {
            ++i;
            ++character;
            while(src[i] != ';') {
                if(src[i] == '\n') {
                    ++line;
                    character = 0;
                }
                ++character;
                ++i;
            }
        }
        if(src[i] == '\n') {
            ++line;
            character = 0;
        }
        ++i;
        ++character;
        }
        if(i <= size && src[i] != 0) {
            switch(src[i]) {
                case 'L':{
                    if(*((i64*)&src[i]) == 0x4354584544414F4C) {
                        printf("LOADLib\n");
                        i += 3;
                        cmdTokenPTR->CommandNumber = 3;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                    }
                    break;
                }

                case 'c':{
                    if(*((i32*)&src[i]) == 0x72616863) {
                        printf("CHAR: ");
                        i += 4;
                        character += 4;
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] == '\n' || src[i] == 0) {
                            printf("INVALID CHAR TYPE: NO NAME\nWARNING: LINE: %llu CHARACTER: %llu\n", line, character);
                            break;
                        }
                        while(src[i] == ' ') {
                            ++i;
                            ++character;
                        }
                        u64 start = i;
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != ';' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        cmdTokenPTR->CommandNumber = 2;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        CharNameTknPtr->CharacterName = (char*)calloc(((i-start) + 1), sizeof(char));
                        strncpy(CharNameTknPtr->CharacterName, &src[start], (i-start));
                        printf("%s\n", CharNameTknPtr->CharacterName);
                        CharNameTknPtr->next = (CharName*)calloc(1, sizeof(CharName));
                        ++CharacterTotal;
                        while(src[i] != '\n' && src[i] != 0 && src[i] != '=') {
                            ++i;
                        }
                        if(src[i] == '\n') {
                            CharNameTknPtr->Default = 0;
                            while(src[i] != '\n' && src[i] != 0) {
                                ++i;
                            }
                            CharNameTknPtr = CharNameTknPtr->next;
                            break;
                        }
                        ++i;
                        while(src[i] == ' ') {
                            ++i;
                        }
                        if(src[i] == '\'') {
                            CharNameTknPtr->Default = src[i+1];
                            if(src[i+2] != '\'') {
                                printf("WARNING: SPECIFYING A CHAR NEEDS A ' ON BOTH SIDES OF THE CHARACTER\n");
                            }
                        } else {
                            CharNameTknPtr->Default = atoi(&src[i]);
                        }
                        printf("CHAR: %c\n", CharNameTknPtr->Default);
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                        CharNameTknPtr = CharNameTknPtr->next;
                    }
                    break;
                }
                
                case 'i':{
                    if(*((i16*)&src[i+1]) == 0x746e) {
                        printf("INT: ");
                        i += 3;
                        character += 3;
                        if(src[i] != ' ') {
                            printf("INVALID INT TYPE: NO NAME 1\nWARNING: LINE: %llu CHARACTER: %llu\n", line, character);
                            while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        while(src[i] != ' ' && src[i] != '\n' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] == '\n' || src[i] == 0) {
                            printf("INVALID INT TYPE: NO NAME 2\nWARNING: LINE: %llu CHARACTER: %llu\n", line, character);
                            break;
                        }
                        while(src[i] == ' ') {
                            ++i;
                            ++character;
                        }
                        u64 start = i;
                        while(src[i] != '=' && src[i] != ' ' && src[i] != '\n' && src[i] != ';' && src[i] != 0) {
                            ++i;
                            ++character;
                        }
                        if(src[i] != ' ' && src[i] != '=' && src[i] != '\n' ) {
                            printf("INVALID INT TYPE\nWARNING: LINE: %llu CHARACTER: %llu\n", line, character);
                            while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        printf("CC\n");
                        if((i - start) <= 0) {
                             printf("INVALID INT TYPE\nWARNING: LINE: %llu CHARACTER: %llu\n", line, character);
                             while(src[i] != '\n') {
                                ++i;
                            }
                            break;
                        }
                        cmdTokenPTR->CommandNumber = 1;
                        cmdTokenPTR->next = (CMDToken*)calloc(1, sizeof(CMDToken));
                        cmdTokenPTR = cmdTokenPTR->next;
                        intNameTKNPTR->IntegerName = (char*)calloc(((i-start) + 1), sizeof(char));
                        intNameTKNPTR->next = (IntName*)calloc(1, sizeof(IntName));
                        ++IntegersTotal;
                        if((i - start) == 1) {
                            intNameTKNPTR->IntegerName[0] = src[start];
                        } else {
                        strncpy(intNameTKNPTR->IntegerName, &src[start], (i-start));
                        }
                        printf("%s\n", intNameTKNPTR->IntegerName);
                        while(src[i] != '\n' && src[i] != 0 && src[i] != '=') {
                            ++i;
                        }
                        if(src[i] == '\n') {
                            intNameTKNPTR->Default = 0;
                            intNameTKNPTR = intNameTKNPTR->next;
                            break;
                        }
                        ++i;
                        while(src[i] == ' ') {
                            ++i;
                        }
                        intNameTKNPTR->Default = atoi(&src[i]);
                        while(src[i] != '\n' && src[i] != 0) {
                            ++i;
                        }
                        intNameTKNPTR = intNameTKNPTR->next;
                    }
                    break;
                }
                defalt:{
                    break;
                }
            }
            if(src[i] == '\n') {
            ++line;
            character = 0;
        }
            ++i;
        }
    }


    return;
}

void TokenToFile(const i8* outName) {
    CMDToken* cmdTokenPTR = commandsTokenList;
    IntName* intNameTKNPTR = IntegerTokenList;
    CharName* CharNameTknPtr = CharacterTokenList;
    u64 integers = 0, characters = 0;
    i8 Inttt = 0, charrr = 0;
    if(IntegersTotal > 0xFF && IntegersTotal <= 0xFFFF) {
        Inttt = 1;
    } else if(IntegersTotal > 0xFFFF && IntegersTotal <= 0xFFFFFFFF) {
        Inttt = 2;
    } else if(IntegersTotal > 0xFFFFFFFF && IntegersTotal <= 0xFFFFFFFFFFFFFFFF) {
        Inttt = 3;
    }
    if(CharacterTotal > 0xFF && CharacterTotal <= 0xFFFF) {
        charrr = 1;
    } else if(CharacterTotal > 0xFFFF && CharacterTotal <= 0xFFFFFFFF) {
        charrr = 2;
    } else if(CharacterTotal > 0xFFFFFFFF && CharacterTotal <= 0xFFFFFFFFFFFFFFFF) {
        charrr = 3;
    }
    FILE* outputFile = (void*)0;
    outputFile = fopen64(outName, "w");
    if(outputFile == (void*)0) {
        return;
    }
    fwrite("HAZLCPL                       D", 11, 3, outputFile);
    fputc(Inttt, outputFile);
    fputc(charrr, outputFile);
    while(cmdTokenPTR) {
    CMDToken *temp = cmdTokenPTR->next;
    switch(cmdTokenPTR->CommandNumber) {
        case 1:{
            fputc(0x00, outputFile);

            fputc(((integers)& 0xFF), outputFile);
            if(Inttt > 0){
            fputc(((integers >> 8)& 0xFF), outputFile);
            }
            if(Inttt > 1){
            fputc(((integers >> 16)& 0xFF), outputFile);
            fputc(((integers >> 24)& 0xFF), outputFile);
            }
            if(Inttt > 2){
            fputc(((integers >> 32)& 0xFF), outputFile);
            fputc(((integers >> 40)& 0xFF), outputFile);
            fputc(((integers >> 48)& 0xFF), outputFile);
            fputc(((integers >> 56)& 0xFF), outputFile);
            }
            if(intNameTKNPTR->Default == 0) {
                fputc(0x00, outputFile);
            } else {
                fputc(0x01, outputFile);
                fputc(((intNameTKNPTR->Default >> 0)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 8)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 16)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 24)& 0xFF), outputFile);
            }
            intNameTKNPTR = intNameTKNPTR->next;
            ++integers;
            break;
        }
        case 2:{
            fputc(0x01, outputFile);
            fputc(((characters)& 0xFF), outputFile);
            if(charrr > 0) {
            fputc(((characters >> 8)& 0xFF), outputFile);
            }
            if(charrr > 1) {
            fputc(((characters >> 16)& 0xFF), outputFile);
            fputc(((characters >> 24)& 0xFF), outputFile);
            }
            if(charrr == 3) {
            fputc(((characters >> 32)& 0xFF), outputFile);
            fputc(((characters >> 40)& 0xFF), outputFile);
            fputc(((characters >> 48)& 0xFF), outputFile);
            fputc(((characters >> 56)& 0xFF), outputFile);
            }
            fputc(CharNameTknPtr->Default, outputFile);
            CharNameTknPtr = CharNameTknPtr->next;
            ++characters;
            break;
        }
        case 3:{
            fputc(0x02, outputFile);
            break;
        }
        default:{
            break;
        }
    }      
    cmdTokenPTR = temp;
    }
    fclose(outputFile);
    intNameTKNPTR = IntegerTokenList;
while (intNameTKNPTR) {
  IntName *temp = intNameTKNPTR->next;
  free(intNameTKNPTR);
  intNameTKNPTR = temp;
}

CharNameTknPtr = CharacterTokenList;
while (CharNameTknPtr) {
  CharName *temp = CharNameTknPtr->next;
  free(CharNameTknPtr);
  CharNameTknPtr = temp;
}

cmdTokenPTR = commandsTokenList;
while (cmdTokenPTR) {
  CMDToken *temp = cmdTokenPTR->next;
  free(cmdTokenPTR);
  cmdTokenPTR = temp;
}

return;
    return;
}

void TokenToFileDebug(const i8* outName) {
    CMDToken* cmdTokenPTR = commandsTokenList;
    IntName* intNameTKNPTR = IntegerTokenList;
    CharName* CharNameTknPtr = CharacterTokenList;
    u64 integers = 0, characters = 0;
    i8 Inttt = 0, charrr = 0;
    if(IntegersTotal > 0xFF && IntegersTotal <= 0xFFFF) {
        Inttt = 1;
    } else if(IntegersTotal > 0xFFFF && IntegersTotal <= 0xFFFFFFFF) {
        Inttt = 2;
    } else if(IntegersTotal > 0xFFFFFFFF && IntegersTotal <= 0xFFFFFFFFFFFFFFFF) {
        Inttt = 3;
    }
    if(CharacterTotal > 0xFF && CharacterTotal <= 0xFFFF) {
        charrr = 1;
    } else if(CharacterTotal > 0xFFFF && CharacterTotal <= 0xFFFFFFFF) {
        charrr = 2;
    } else if(CharacterTotal > 0xFFFFFFFF && CharacterTotal <= 0xFFFFFFFFFFFFFFFF) {
        charrr = 3;
    }
    FILE* outputFile = (void*)0;
    outputFile = fopen64(outName, "w");
    if(outputFile == (void*)0) {
        printf("OUTPUT FILE: \"%s\"COULD NOT BE CREATED OR OPENED\n", outName);
        return;
    }
    fwrite("HAZLCPL                       D", 11, 3, outputFile);
    fputc(Inttt, outputFile);
    fputc(charrr, outputFile);
    printf("%llu, %llu\n", IntegersTotal, CharacterTotal);
    while(cmdTokenPTR) {
    CMDToken *temp = cmdTokenPTR->next;
    switch(cmdTokenPTR->CommandNumber) {
        case 1:{
            printf("INT\n");
            fputc(0x00, outputFile);

            fputc(((integers)& 0xFF), outputFile);
            if(Inttt > 0){
            fputc(((integers >> 8)& 0xFF), outputFile);
            }
            if(Inttt > 1){
            fputc(((integers >> 16)& 0xFF), outputFile);
            fputc(((integers >> 24)& 0xFF), outputFile);
            }
            if(Inttt > 2){
            fputc(((integers >> 32)& 0xFF), outputFile);
            fputc(((integers >> 40)& 0xFF), outputFile);
            fputc(((integers >> 48)& 0xFF), outputFile);
            fputc(((integers >> 56)& 0xFF), outputFile);
            }
            if(intNameTKNPTR->Default == 0) {
                fputc(0x00, outputFile);
            } else {
                fputc(0x01, outputFile);
                printf("%i\n", intNameTKNPTR->Default);
                fputc(((intNameTKNPTR->Default >> 0)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 8)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 16)& 0xFF), outputFile);
                fputc(((intNameTKNPTR->Default >> 24)& 0xFF), outputFile);
            }
            intNameTKNPTR = intNameTKNPTR->next;
            ++integers;
            break;
        }
        case 2:{
            printf("CHAR: %c\\%i\n", CharNameTknPtr->Default, CharNameTknPtr->Default);
            fputc(0x01, outputFile);
            fputc(((characters)& 0xFF), outputFile);
            if(charrr > 0) {
            fputc(((characters >> 8)& 0xFF), outputFile);
            }
            if(charrr > 1) {
            fputc(((characters >> 16)& 0xFF), outputFile);
            fputc(((characters >> 24)& 0xFF), outputFile);
            }
            if(charrr == 3) {
            fputc(((characters >> 32)& 0xFF), outputFile);
            fputc(((characters >> 40)& 0xFF), outputFile);
            fputc(((characters >> 48)& 0xFF), outputFile);
            fputc(((characters >> 56)& 0xFF), outputFile);
            }
            fputc(CharNameTknPtr->Default, outputFile);
            CharNameTknPtr = CharNameTknPtr->next;
            ++characters;
            break;
        }
        case 3:{
            printf("EXTERNAL LIB\n");
            fputc(0x02, outputFile);
            break;
        }
        default:{
            break;
        }
    }      
    cmdTokenPTR = temp;
    }
    fclose(outputFile);
    intNameTKNPTR = IntegerTokenList;
while (intNameTKNPTR) {
  IntName *temp = intNameTKNPTR->next;
  free(intNameTKNPTR);
  intNameTKNPTR = temp;
}

CharNameTknPtr = CharacterTokenList;
while (CharNameTknPtr) {
  CharName *temp = CharNameTknPtr->next;
  free(CharNameTknPtr);
  CharNameTknPtr = temp;
}

cmdTokenPTR = commandsTokenList;
while (cmdTokenPTR) {
  CMDToken *temp = cmdTokenPTR->next;
  free(cmdTokenPTR);
  cmdTokenPTR = temp;
}

return;
}