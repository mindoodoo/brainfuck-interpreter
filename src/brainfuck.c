/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include "brainfuck.h"

// Initializes bf_state_t
bf_state_t *init_tape(char *filename) {
    bf_state_t *s = (bf_state_t*) calloc(1, sizeof(bf_state_t));

    s->tape = (byte*) calloc(TAPE_SIZE, sizeof(byte));
    s->tape_size = TAPE_SIZE;

    if (!(s->pgm = read_file(filename))) {
        free(s->tape);
        free(s);
        return NULL;
    }

    return s;
}