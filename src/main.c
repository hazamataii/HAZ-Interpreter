#include "types.h"
#include <stdio.h>

#ifdef _WIN32
#ifndef UNICODE
#define UNICODE
#endif 
#include <windows.h>
#include <stdlib.h>
i32 WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, u16* lpCmdLine, i32 nCmdShow) {
u16** argc = (void*)0;
i32 arcv = 0;
argc = CommandLineToArgvW(GetCommandLineW(), &arcv);
if(argc == (void*)0) {
    return -1;
}
i8** argv = (void*)0;
argv = (i8**)calloc(arcv, sizeof(i8*));
if(argv == (void*)0) {
    return -1;
}
i32 argConvIndex = 0;
while(argConvIndex < arcv) {
i32 tmp = WideCharToMultiByte(CP_UTF8, 0, argc[argConvIndex], -1, (void*)0, 0, 0, 0);
argv[argConvIndex] = (i8*)calloc(tmp, sizeof(i8));
if(argv[argConvIndex] == (void*)0) {
    return -1;
}
WideCharToMultiByte(CP_UTF8, 0,argc[argConvIndex], -1, argv[argConvIndex], tmp, 0, 0);
++argConvIndex;

}
i32 i = 0;
/*while(i < arcv) {
    printf("%i\n", i);
    free(argc[i]);
    ++i;
}
free(argc);*/
#else 
i32 main(i32 arcv, i8** argv) {
#endif
u8 RunFlags = 0;
printf("T\n");
i32 srcI = 0, ARGSi = 0, playI = 0, outI = 0, argI = 0;
i16 TMP = 0;
while(argI < arcv){
TMP = *((i16*)argv[argI]);
if(argv[argI][0] == 45){
switch(TMP) {
    case 0x642D:{
    }
    case 0x442D:{
        if((RunFlags &(1 << 0)) == 0b00000000) {
        /*printf("DEBUG MODE ACTIVE\n");*/
        RunFlags += 0b00000001;
        }
        break;
    }
    case 0x632D:{
    }
    case 0x432D:{
        if((RunFlags &(1 << 1)) < 0b00000010){
       /* printf("COMPILE MODE ACTIVE\n");*/
        RunFlags |= 0b00000010;
        }
        break;
    }
    case 0x2D2D:{
        u32 OTMP = *((u32*)&argv[argI][2]);
        if(OTMP = 0x73677261) {
            ARGSi = argI + 1;
            argI = arcv;
        }
        break;
    }
    case 0x6F2D:{
    }
    case 0x4F2D:{
        outI = argI + 1;
        break;
    }
    case 0x732D:{
    }
    case 0x532D:{
        srcI = argI + 1;
        break;
    }
    default:{
/*        printf("THE ARGUMENT \"%ls\" IS INVALID\n", argv[argI]);*/
        break;
    }
}} else {
    playI = argI;
}
++argI;
}

#ifdef _WIN32
#include "win/win.h"
printf("HERE\n");
if((RunFlags & (1 << 1)) >= 0b00000010){
if((RunFlags & (1 << 0)) == 0b00000000){
CompileNormal(srcI, outI, argv);
} else {
CompileDebug(srcI, outI, argv);
}
} else {
if((RunFlags & (1 << 0)) == 0b00000000){
RunNormal(playI, ARGSi, argv, arcv);
} else {
RunDebug(playI, ARGSi, argv, arcv);
}
}
#else
#include "linux/linux.h"
printf("HERE\n");
if((RunFlags & (1 << 1)) >= 0b00000010){
if((RunFlags & (1 << 0)) == 0b00000000){
CompileNormal(srcI, outI, argv);
} else {
CompileDebug(srcI, outI, argv);
}
} else {
if((RunFlags & (1 << 0)) == 0b00000000){
RunNormal(playI, ARGSi, argv, arcv);
} else {
RunDebug(playI, ARGSi, argv, arcv);
}
}
#endif











#ifdef _WIN32
i = 0;
while(i < arcv) {
    free(argv[i]);
    ++i;
}

free(argv);
return 0;
}
#else 
return 0;
}
#endif