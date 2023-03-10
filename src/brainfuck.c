/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include "brainfuck.h"

bf_state_t *init_tape(void) {
    bf_state_t *tape = (bf_state_t*) calloc(1, sizeof(bf_state_t));

    tape->tape = (byte*) calloc(TAPE_SIZE, sizeof(byte));
    tape->tape_size = TAPE_SIZE;
    return tape;
}