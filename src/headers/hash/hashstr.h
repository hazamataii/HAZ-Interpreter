#ifndef __HASHSTR_H__
#define __HASHSTR_H__

void hashSetString(const char* __restrict__ str, unsigned int** __restrict__ hashTable, const unsigned int maxPos);
void hashSetStringNoTable(const char* __restrict__ str);
unsigned int hashCheckStringPos(const char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos);
unsigned int hashCheckStringValue(const char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos);
unsigned int hashCheckStringValueNoTable(const char* __restrict__ str);
#endif