#include "cmd.h"
#include "../types.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

void MakeAndUseConsole() {
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    i64 hCrt = _open_osfhandle((i64) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, (void*)0, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((i64) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, (void*)0, _IONBF, 128);
    *stdin = *hf_in;
}