/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include <stdlib.h>
#include "brainfuck.h"

// Read file into byte buffer
byte* read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");  // Open file in binary mode
    if (!file) {
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    byte *file_content = (byte*) calloc(file_size, 1);
    if (!file_content) {
        fclose(file);
        return NULL;
    }

    // Read file contents
    fread(file_content, 1, file_size, file);
    fclose(file);
    return file_content;
}