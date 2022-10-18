#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "../types.h"

void Tokenizer(const  i8* src, const u64 size);
void TokenizerDebug(const  i8* src , const u64 size);
void TokenToFile(const i8* outputFile);
void TokenToFileDebug(const i8* outputFile);

#endif