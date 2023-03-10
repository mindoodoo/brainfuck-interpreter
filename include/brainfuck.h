/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#pragma once

#include <stdlib.h>

#define TAPE_SIZE 20000

// ─── Brainfuck State ─────────────────────────────────────────────────────────────────────────────

typedef unsigned char byte;

typedef struct bf_state_s {
    byte *tape;
    size_t tape_size;
} bf_state_t;

// Initializes empty tape of size TAPE_SIZE
bf_state_t *init_tape(void);