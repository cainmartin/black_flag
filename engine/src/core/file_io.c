//
// Created by Cain Martin on 2025/08/07.
//

#include <stdlib.h>
#include <stdio.h>
#include "file_io.h"

char* read_file(const char* path, size_t* size)
{
    FILE* file = fopen(path, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    const size_t file_size = ftell(file);
    rewind(file);

    char* buffer = malloc(file_size + 1);
    if (!buffer)
    {
        fclose(file);
        fprintf(stderr, "Unable to open file %s\n", path);
        return NULL;
    }

    fread(buffer, 1, file_size, file);

    buffer[file_size] = '\0';
    *size = file_size;

    fclose(file);

    return buffer;
}