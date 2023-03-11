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
    // Tape
    byte *tape;
    size_t tape_size;
    size_t tape_head;
    // Program
    byte *pgm;
    size_t pgm_size;
    size_t pgm_head;
} bf_state_t;

// Initializes bf_state_t
// also loads program
bf_state_t *init_state(char *filename);

// ─── Utilities ───────────────────────────────────────────────────────────────────────────────────

byte* read_file(const char *filename, size_t *size);