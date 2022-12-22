#ifndef __FILE_H__
#define __FILE_H__

int fileRead(char const* __restrict__ filePath, char** __restrict__ dest, int const parsing);
int fileWrite(char const* __restrict__ filePath, char const* __restrict__ content, unsigned long long int const length);
#endif