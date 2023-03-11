/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include "brainfuck.h"

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

// Runs instruction pointed at by pgm_head
int run_head(bf_state_t *s) {
    char instr = head_instr(s);
    int output = 0;

    switch (instr) {
        case '>':
            s->tape_head++;
            s->pgm_head++;
            break;
        case '<':
            s->tape_head--;
            s->pgm_head++;
            break;
        case '+':
            s->tape[s->tape_head]++;
            s->pgm_head++;
            break;
        case '-':
            s->tape[s->tape_head]--;
            s->pgm_head++;
            break;
        case '.':
            UNIMPLEMENTED
            break;
        case ',':
            UNIMPLEMENTED
            break;
        case '[':
            UNIMPLEMENTED
            break;
        case ']':
            UNIMPLEMENTED
            break;
        default:
            s->pgm_head++;
            break;
    }

    return output;
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

// Runs program loaded into state
int run_state(bf_state_t *s) {
    int output = 0;

    while ((output = is_state_valid(s)))
        if ((output = run_head(s)))
            break;
    return output;
}