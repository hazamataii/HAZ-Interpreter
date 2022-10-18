#ifndef __LINUX_H__
#define __LINUX_H__
#include "../types.h"

void CompileNormal(i32 SRCi, i32 OUTi, i8** args);
void CompileDebug(i32 SRCi, i32 OUTi, i8** args);

void RunNormal(i32 PLAYi, i32 ARGSi, i8** args, i32 arcv);
void RunDebug(i32 PLAYi, i32 ARGSi, i8** args, i32 arcv);

#endif