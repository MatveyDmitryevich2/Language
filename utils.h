#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stddef.h>

struct Info_buffer
{
    char* buffer;
    size_t size;
};

#define USE_DEBUG_PRINTF

#ifdef USE_DEBUG_PRINTF
    #define DPRINTF(str, ...) fprintf(stderr, str, __VA_ARGS__)
#else
    #define DPRINTF(str, ...) ;
#endif

static const char NAME_FILE_CTOR[] = "proga.txt";

void Read_file_buffer(const char* name_file, Info_buffer* info_buffer);
size_t Get_file_size(FILE *file);
bool Is_operator(char simbol);


#endif //UTILS_H