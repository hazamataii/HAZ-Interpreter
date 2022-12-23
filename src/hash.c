#include "headers/hash/hashStr.h"
#include <string.h>

#include <stdio.h>
void hashSetStringNoTable(char* __restrict__ str) {

    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    char *s = str;
    for(; *s; ++s)
    {
        hash_Value += *s;
        hash_Value += (hash_Value << 10);
        hash_Value ^= (hash_Value >> 6);
    }

    hash_Value += (hash_Value << 3);
    hash_Value ^= (hash_Value >> 11);
    hash_Value += (hash_Value << 15);
    printf("Str:%s Value:%u\n", str, hash_Value);
    return;

}

void hashSetString(char* __restrict__ str, unsigned int** __restrict__ hashTable, const unsigned int maxPos) {

    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    char *s = str;
    for(; *s; ++s)
    {
        hash_Value += *s;
        hash_Value += (hash_Value << 10);
        hash_Value ^= (hash_Value >> 6);
    }

    hash_Value += (hash_Value << 3);
    hash_Value ^= (hash_Value >> 11);
    hash_Value += (hash_Value << 15);
    /*Make sure Position exists in hashTable*/
    register unsigned int Pos = hash_Value % maxPos;
    /*Check default spot*/
    if(hashTable[0][Pos] == 0){
    hashTable[0][Pos] = hash_Value;
    /*Try spot 0*/
    } else if(hashTable[0][0] == 0){
    Pos = 0;
    hashTable[0][Pos] = hash_Value;
    /*Go through hashTable until open spot*/
    } else {
        Pos = 1;
        while(hashTable[0][Pos] != 0) {
            ++Pos;
        }
        hashTable[0][Pos] = hash_Value;
    }
    return;
}

unsigned int hashCheckStringPos(char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos) {

    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    char *s = str;
    for(; *s; ++s)
    {
        hash_Value += *s;
        hash_Value += (hash_Value << 10);
        hash_Value ^= (hash_Value >> 6);
    }

    hash_Value += (hash_Value << 3);
    hash_Value ^= (hash_Value >> 11);
    hash_Value += (hash_Value << 15);

    /*Make sure Position exists in hashTable*/
    register unsigned int Pos = hash_Value % maxPos;
    //printf("STR:%s POS:%u VALUE:%u MAX:%u\n", str, Pos, hash_Value, maxPos);
    /*Check default spot*/
    if(hashTable[Pos] == hash_Value){
    return Pos;
    /*Try spot 0*/
    } else if(hashTable[0] == 0){
    return 0;
    /*Go through hashTable until the end or it is found*/
    } else {
        Pos = 1;
        while(hashTable[Pos] != hash_Value && Pos < maxPos) {
            ++Pos;
        }
        if(Pos < maxPos) {
            return Pos;
        }
    }
    /*If not found, return maxPos (Invalid spot on hashTable)*/
    return maxPos;
}

unsigned int hashCheckStringValue(char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos) {
    
    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    char *s = str;
    for(; *s; ++s)
    {
        hash_Value += *s;
        hash_Value += (hash_Value << 10);
        hash_Value ^= (hash_Value >> 6);
    }

    hash_Value += (hash_Value << 3);
    hash_Value ^= (hash_Value >> 11);
    hash_Value += (hash_Value << 15);
    /*Make sure Position exists in hashTable*/
    register unsigned int Pos = hash_Value % maxPos;
    /*Check default spot*/
    //if(hashTable[Pos] == hash_Value){
    return hash_Value;
}

unsigned int hashCheckStringValueNoTable(char* __restrict__ str) {
    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    char *s = str;
    for(; *s; ++s)
    {
        hash_Value += *s;
        hash_Value += (hash_Value << 10);
        hash_Value ^= (hash_Value >> 6);
    }

    hash_Value += (hash_Value << 3);
    hash_Value ^= (hash_Value >> 11);
    hash_Value += (hash_Value << 15);

    return hash_Value;
}