#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

bool Is_operator(char simbol)
{
    return (simbol == '+' || simbol == '-' || simbol == '/' || simbol == '*' || simbol == '^');
}

size_t Get_file_size(FILE *file)
{
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    size_t size_file = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    return size_file;
}

void Read_file_buffer(const char* name_file, Info_buffer* info_buffer)
{
    assert(name_file != NULL);

    FILE* file_for_save = fopen(name_file, "r");

    info_buffer->size = Get_file_size(file_for_save);
    info_buffer->buffer = (char*)calloc(info_buffer->size + 1, sizeof(char));

    fread(info_buffer->buffer, sizeof(char), info_buffer->size, file_for_save);

    fclose(file_for_save);
}