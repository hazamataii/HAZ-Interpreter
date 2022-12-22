#ifdef _WIN32
/*If building for windows*/
/*Allow for utf-16 entry point*/
#ifndef UNICODE
#define UNICODE
#endif
/*Small windows api*/
#include <stdio.h>
#include "headers/win.h"
#include <shellapi.h>
INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, INT nCmdShow) {

#include <stdlib.h>
/*Convert utf-16 to utf-8*/
LPWSTR* argc = (void*)0;
int arcv = 0;
/*Get Arguments*/
argc = CommandLineToArgvW(GetCommandLineW(), &arcv);
if(argc == (void*)0) {
    return -1;
}
char** argv = (void*)0;
argv = (char**)calloc(arcv, sizeof(char*));
if(argv == (void*)0) {
    return -1;
}
int argConvIndex = 0;
while(argConvIndex < arcv) {
/*Get UTF-8 length*/
int tmp = WideCharToMultiByte(CP_UTF8, 0, argc[argConvIndex], -1, (void*)0, 0, 0, 0);
argv[argConvIndex] = (char*)calloc(tmp, sizeof(char));
if(argv[argConvIndex] == (void*)0) {
    return -1;
}
/*Get UTF-8 char array*/
WideCharToMultiByte(CP_UTF8, 0,argc[argConvIndex], -1, argv[argConvIndex], tmp, 0, 0);
++argConvIndex;

}

/*Set Work Directory to executable*/
char* TmpWorkFilePath = (char*)calloc(strlen(argv[0]), sizeof(char));
memcpy(TmpWorkFilePath, argv[0], (strlen(argv[0])-19));
//printf("%s\n", TmpWorkFilePath);

SetCurrentDirectoryA(TmpWorkFilePath);
free(TmpWorkFilePath);

#else 
/*Linux entry point*/
int main(int arcv, char** argv){
#endif
#include "headers/flags.h"
char Flags = 0;
register unsigned long long int i = 2;
char* playableFile = argv[1];

/*Check Arguments*/
while(i < arcv) {
    printf("%s\n", argv[i]);
    if(argv[i][0] == '-') {
        switch(argv[i][1]) {
            case 'C':
            case 'c':{
                printf("COMPILE MODE ACTIVE\n");
                Flags += COMPILEMODE;
                break;
            }
            case 'D':
            case 'd':{
                printf("DEBUG MODE ACTIVE\n");
                Flags += DEBUGMODE;
                break;
            }
            default:{
                printf("INVALID ARGUMENT: \"%s\"\n", argv[i]);
                break;
            }
        }
    }
    ++i;
}

if(Flags & COMPILEMODE) {
    /*Compile Mode*/
    if(Flags & DEBUGMODE) {
        /*Debug Mode*/
    } else {
        /*No Debug Mode*/
        #include "headers/compile/compile.h"
        compile(&playableFile);
    }
} else {
    /*Run Mode*/
    if(Flags & DEBUGMODE) {
        /*Debug Mode*/
    } else {
        /*No Debug Mode*/
        #include <string.h>
        if(playableFile[strlen(playableFile)-1] == 'l') {
            #include "headers/run/run.h"
            run(&playableFile);
        } else if(playableFile[strlen(playableFile)-1] == 'b') {
            #include "headers/run/bytecode/runByte.h"
            runByte(&playableFile);
        }
    }
}

return 0;
}