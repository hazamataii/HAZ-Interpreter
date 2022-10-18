#include "file.h"

#include <stdio.h>
#include <stdlib.h>

i32 ReadFileNoMem(const i8* src, i8** dest, u64* size) {

FILE* f = (void*)0;
if((f = fopen64(src, "r")) == (void*)0) {
    return -1;
}
if(_fseeki64(f, 0L, SEEK_END) != 0) {
    fclose(f);
    return -2;
};
*size = _ftelli64(f);
if(*size == 0) {
    fclose(f);
    return -3;
}
if(_fseeki64(f, 0L, SEEK_SET) != 0){
fclose(f);
return -4;
}
 *dest = (i8*)calloc(*size+1, 1);
    if(*dest == (void*)0) {
        fclose(f);
        return -5;
    }
fread(*dest, 1, *size, f);
fclose(f);
}