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
    FILE *file = fopen(filename, "rb");  // Open the file in binary mode
    if (!file) {
        return NULL;  // Return NULL if the file could not be opened
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    byte *file_content = (byte*) calloc(file_size, 1);
    if (!file_content) {
        fclose(file);
        return NULL;  // Return NULL if memory allocation failed
    }

    // Read the file content into the buffer
    fread(file_content, 1, file_size, file);

    fclose(file);  // Close the file

    return file_content;  // Return the buffer containing the file content
}