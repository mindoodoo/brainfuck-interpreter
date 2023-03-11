/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include <stdlib.h>
#include "brainfuck.h"

// Read file into byte buffer
char* read_file(const char *filename, size_t *size) {
    FILE *file = fopen(filename, "rb");  // Open file in binary mode
    if (!file) {
        return NULL;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = (char*) calloc(*size, 1);
    if (!file_content) {
        fclose(file);
        return NULL;
    }

    // Read file contents
    fread(file_content, 1, *size, file);
    fclose(file);
    return file_content;
}

// Initializes bf_state_t
bf_state_t *init_state(char *filename) {
    bf_state_t *s = (bf_state_t*) calloc(1, sizeof(bf_state_t));

    s->tape = (byte*) calloc(TAPE_SIZE, sizeof(byte));
    s->tape_size = TAPE_SIZE;

    if (!(s->pgm = read_file(filename, &s->pgm_size))) {
        free(s->tape);
        free(s);
        return NULL;
    }

    return s;
}

int is_state_valid(bf_state_t *s) {
    if (s->tape_head >= s->tape_size) {
        fprintf(stderr, "Error: tape head has overflowed.");
        return HEAD_OVERFLOW;
    }
    if (s->pgm_head >= s->pgm_size)
        return PGM_OVER;
    return 0;
}

int move_to_corresponding_bracket(bf_state_t *s) {
    int step;
    char target;
    char opening;
    int opening_count = 0;
    int closing_count = 0;
    char head_instruction = head_instr(s);

    if (head_instruction != '[' && head_instruction != ']')
        return 1;

    if (head_instruction == '[') {
        step = 1;
        target = ']';
        opening = '[';
    } else if (head_instruction == ']') {
        step = -1;
        target = '[';
        opening = ']';
    } else
        return 0;

    while (opening_count != closing_count) {
        head_instruction = head_instr(s);

        if (head_instruction == opening)
            opening_count++;
        else if (head_instruction == target)
            closing_count++;
        if (s->pgm_head == 0 || s->pgm_head == s->tape_size - 1)
            return 1;
        s->pgm_head += step;
    }

    return 0;
}
