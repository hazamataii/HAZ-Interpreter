#include "linux.h"
#include <stdio.h>
#include <stdlib.h>
#include "../win/file/file.h"
#include "../tokens/token.h"


void CompileNormal(i32 SRCi, i32 OUTi, i8** args) {
    if(SRCi == 0) {
        return;
    }
    if(OUTi == 0) {
        return;
    }
    i8* src = (void*)0;
    u64 size = 0;
    if(ReadFileNoMem(args[SRCi], &src, &size) != 0) {
        return;
    }
    Tokenizer(src, size);
    TokenToFile(args[OUTi]);

    free(src);

    return;
}

void CompileDebug(i32 SRCi, i32 OUTi, i8** args) {
    MakeAndUseConsole();
    if(SRCi == 0) {
        printf("NO CHOSEN SOURCE. USE \"-s\" OR \"-S\" FOLLOWED BY A SOURCE FILE\n");
        return;
    }
    if(OUTi == 0) {
        printf("NO CHOSEN OUTPUT. USE \"-o\" OR \"-O\" FOLLOWED BY AN OUTPUT FILE\n");
        return;
    }
    printf("SOURCE FILE:%ls\nOUTPUT FILE:%s\n",args[SRCi], args[OUTi]);
    i8* src = (void*)0;
    u64 size = 0;
    switch(ReadFileNoMem(args[SRCi], &src, &size)) {
        case -1:{
            printf("FILE: \"%s\" FAILED TO BE OPENED\n", args[SRCi]);
            return;
            break;
        }
        case -2:{
            printf("FILE: \"%s\" FAILED TO SEEK TO THE END OF THE FILE\n", args[SRCi]);
            return;
            break;
        }
        case -3:{
            printf("FILE: \"%s\" FAILED TO GET SIZE OR SIZE IS 0\n", args[SRCi]);
            return;
            break;
        }
        case -4:{
            printf("FILE: \"%s\" FAILED TO GET BACK TO THE START OF THE FILE\n", args[SRCi]);
            return;
            break;
        }
        case -5:{
            printf("FILE: \"%s\" FAILED TO ALLOCATE THE MEMORY NEEDED TO STORE FILE\n", args[SRCi]);
            return;
            break;
        }
        default:{
            printf("FILE: \"%s\" READ SUCCESSFULLY\n", args[SRCi]);
            break;
        }
    }

    TokenizerDebug(src, size);
    TokenToFileDebug(args[OUTi]);

    free(src);

    return;
}

void RunNormal(i32 PLAYi, i32 ARGSi, i8** args, i32 arcv) {
    if(PLAYi == 0) {
        return;
    }
    
    i8* src = (void*)0;
    u64 size = 0;
    if(ReadFileNoMem(args[PLAYi], &src, &size) != 0) {
        return;
    }
    u64 i = 0;
    if((*((u64*)&src[i])) == 0x4C50434C5A41487F) {
        i += 8;
        if((*((u64*)&src[i])) == 0x0000000000000001 && (*((u64*)&src[i+8])) == 0x0000000000000000 && (*((u64*)&src[i+16])) == 0x0000000000000000 && src[i+24] == 'D') {
        } else {
        }
        i += 25;
        i8 integers = src[i], characters = src[i+1];
        i+= 2;
        while(i < (size-1)) {
        switch(src[i]) {
            case 0:{
                ++i;
                if(integers == 0) {
                    ++i;
                }
                if(integers == 1) {
                    i += 2;
                }
                if(integers == 2) {
                    i += 4;
                }
                if(integers == 3) {
                    i += 8;
                }
                if(src[i] == 0) {
                ++i;
                } else {
                ++i;
                i += 4;
                }
                break;
            }
            case 1:{
                i+=2;
                if(characters == 1) {
                    ++i;
                }
                if(characters == 2) {
                    i += 3;
                }
                if(characters == 3) {
                    i += 7;
                }
                ++i;
                break;
            }
            case 2:{
                i++;
                break;
            }
        }
        }
    }

    return;
}



void RunDebug(i32 PLAYi, i32 ARGSi, i8** args, i32 arcv) {
    MakeAndUseConsole();
    if(PLAYi == 0) {
        printf("A FILE IS NEEDED TO RUN\n");
        return;
    }
    printf("PLAYING FILE:%s\n", args[PLAYi]);
    
    i8* src = (void*)0;
    u64 size = 0;
    switch(ReadFileNoMem(args[PLAYi], &src, &size)) {
        case -1:{
            printf("FILE: \"%s\" FAILED TO BE OPENED\n", args[PLAYi]);
            return;
            break;
        }
        case -2:{
            printf("FILE: \"%s\" FAILED TO SEEK TO THE END OF THE FILE\n", args[PLAYi]);
            return;
            break;
        }
        case -3:{
            printf("FILE: \"%s\" FAILED TO GET SIZE OR SIZE IS 0\n", args[PLAYi]);
            return;
            break;
        }
        case -4:{
            printf("FILE: \"%s\" FAILED TO GET BACK TO THE START OF THE FILE\n", args[PLAYi]);
            return;
            break;
        }
        case -5:{
            printf("FILE: \"%s\" FAILED TO ALLOCATE THE MEMORY NEEDED TO STORE FILE\n", args[PLAYi]);
            return;
            break;
        }
        default:{
            printf("FILE: \"%s\" READ SUCCESSFULLY\n", args[PLAYi]);
            break;
        }
    }

    u64 i = 0;
    if((*((u64*)&src[i])) == 0x4C50434C5A41487F) {
        printf("PRECOMPILED\n");
        i += 8;
        printf("VERSION:\nMAJOR: %llu\nMINOR: %llu\nREVISION: %llu\nBUILD LETTER: %c\n", (*((u64*)&src[i])), (*((u64*)&src[i+8])), (*((u64*)&src[i+16])), src[i+24]);
        if((*((u64*)&src[i])) == 0x0000000000000001 && (*((u64*)&src[i+8])) == 0x0000000000000000 && (*((u64*)&src[i+16])) == 0x0000000000000000 && src[i+24] == 'D') {
            printf("PLAYING FILE IS THE SAME VERSION AS INTERPRETER\n");
        } else {
            printf("WARNING: PLAYING FILE IS THE DIFFERENT VERSION AS INTERPRETER, UNWANTED RESULTS MAY OCCUR\n");
        }
        i += 25;
        i8 integers = src[i], characters = src[i+1];
        printf("INT SIZE:%u, CHAR SIZE:%u\n", integers, characters);
        i+= 2;
        while(i < (size-1)) {
        switch(src[i]) {
            case 0:{
                printf("INTEGER: ");
                ++i;
                if(integers == 0) {
                    ++i;
                }
                if(integers == 1) {
                    i += 2;
                }
                if(integers == 2) {
                    i += 4;
                }
                if(integers == 3) {
                    i += 8;
                }
                if(src[i] == 0) {
                ++i;
                printf("%i\n", 0);
                } else {
                ++i;
                printf("%i\n", (*(i32*)&src[i]));
                i += 4;
                }
                break;
            }
            case 1:{
                printf("CHARACTER: ");
                i+=2;
                if(characters == 1) {
                    ++i;
                }
                if(characters == 2) {
                    i += 3;
                }
                if(characters == 3) {
                    i += 7;
                }
                printf("%c\\%i\n", src[i], src[i]);
                ++i;
                break;
            }
            case 2:{
                printf("EXTERNAL LIB\n");
                i++;
                break;
            }
        }
        }
    }

    return;
}