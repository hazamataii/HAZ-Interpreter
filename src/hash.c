#include "headers/hash/hashStr.h"
#include <string.h>

#include <stdio.h>
void hashSetStringNoTable(const char* __restrict__ str) {

    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    register unsigned int i = 0;
    while(i < Length) {
        hash_Value += str[i];
        hash_Value -= (i-Length);
        ++i;
    }
    printf("Str:%s Value:%u\n", str, hash_Value);
    return;

}

void hashSetString(const char* __restrict__ str, unsigned int** __restrict__ hashTable, const unsigned int maxPos) {

    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    register unsigned int i = 0;
    /*Add character value then subtract location in string by length*/
    while(i < Length) {
        hash_Value += str[i];
        hash_Value -= (i-Length);
        ++i;
    }
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

unsigned int hashCheckStringPos(const char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos) {

    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    register unsigned int i = 0;
    /*Add character value then subtract location in string by length*/
    while(i < Length) {
        hash_Value += str[i];
        hash_Value -= (i-Length);
        ++i;
    }

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

unsigned int hashCheckStringValue(const char* __restrict__ str, const unsigned int* __restrict__ hashTable, const unsigned int maxPos) {
    
    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    register unsigned int i = 0;
    /*Add character value then subtract location in string by length*/
    while(i < Length) {
        hash_Value += str[i];
        hash_Value -= (i-Length);
        ++i;
    }
    /*Make sure Position exists in hashTable*/
    register unsigned int Pos = hash_Value % maxPos;
    /*Check default spot*/
    //if(hashTable[Pos] == hash_Value){
    return hash_Value;
    /*Try spot 0*/
    //} else if(hashTable[0] == hash_Value){
    //return hash_Value;
    /*Go through hashTable until the end or it is found*/
    //} else {
    //    Pos = 1;
    //    while(hashTable[Pos] != hash_Value && Pos < maxPos) {
    //        ++Pos;
    //    }
    //    if(Pos < maxPos) {
    //        return hash_Value;
    //    }
    //}
    /*If not found, return maxPos (Invalid spot on hashTable)*/
    //return 0;
}

unsigned int hashCheckStringValueNoTable(const char* __restrict__ str) {
    /*Get string length*/
    register unsigned int const Length = strlen(str);
    register unsigned int hash_Value = 0;
    register unsigned int i = 0;
    /*Add character value then subtract location in string by length*/
    while(i < Length) {
        hash_Value += str[i];
        hash_Value -= (i-Length);
        ++i;
    }

    return hash_Value;
}