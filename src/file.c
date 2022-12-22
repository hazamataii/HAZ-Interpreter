#include "headers/file/file.h"

#include <stdio.h>
#include <stdlib.h>
int fileRead(char const* __restrict__ filePath, char** __restrict__ dest, int const parsing) {
    FILE* file = (void*)0;
    /*Open file in read*/
    if((file = fopen64(filePath, "r")) == (void*)0) {
        /*Failed to open the file*/
        return -1;
    }
    /*Go to the end of the file*/
    if(_fseeki64(file, 0L, SEEK_END) != 0) {
        /*Failed to get to the end of the file*/
        fclose(file);
        return -2;
    }
    /*Get the file's size*/
    register unsigned long long int const size = _ftelli64(file);
    /*Check if size is 0*/
    if(size == 0) {
        /*File size is 0*/
        fclose(file);
        return -3;
    }
    /*Jump back to the start of the file*/
    if(_fseeki64(file, 0L, SEEK_SET) != 0) {
        /*Failed to get back to the start of file*/
        fclose(file);
        return -4;
    }
    /*Allocate File Size*/
    dest[0] = (char*)calloc((size+1+parsing), sizeof(dest[0][0]));
    /*Check if successful*/
    if(dest[0] == (void*)0) {
        /*Memory allocation failed*/
        fclose(file);
        return -5;
    }

    /*Load file into memory*/
    fread(dest[0], sizeof(dest[0][0]), size, file);
    /*Check for stream error*/
    if(ferror(file) != 0) {
        free(dest[0]);
        fclose(file);
        return -6;
    }

    fclose(file);
    return 0;
}

int fileWrite(char const* __restrict__ filePath, char const* __restrict__ content, unsigned long long int const length) {

    FILE* file = (void*)0;
    if((file = fopen64(filePath, "w")) == (void*)0) {
        /*Failed to open file*/
        return -1;
    }
    fwrite(content, 1, length, file);
    fclose(file);


    return 0;
}