#ifndef __HASHSTR_H__
#define __HASHSTR_H__

void hashSetString(char* __restrict__ str, unsigned int** __restrict__ hashTable, const unsigned int maxPos);
void hashSetStringNoTable(char* __restrict__ str);
unsigned int hashCheckStringPos(char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos);
unsigned int hashCheckStringValue(char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos);
unsigned int hashCheckStringValueNoTable(char* __restrict__ str);
#endif