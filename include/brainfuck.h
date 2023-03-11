/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#pragma once

#include <stdlib.h>
#include <stdio.h>

#define TAPE_SIZE 20000

// ─── Error Codes ─────────────────────────────────────────────────────────────────────────────────

#define PGM_OVER 1
#define HEAD_OVERFLOW 2
#define NO_MATCHING_BRACKET 3

// ─── Brainfuck State ─────────────────────────────────────────────────────────────────────────────

typedef unsigned char byte;

typedef struct bf_state_s {
    // Tape
    byte *tape;
    size_t tape_size;
    size_t tape_head;
    // Program
    char *pgm;
    size_t pgm_size;
    size_t pgm_head;
} bf_state_t;


// Runs instruction pointed at by pgm_head
int run_head(bf_state_t *s);

// Runs program loaded into state
int run_state(bf_state_t *s);

// ─── Utilities ───────────────────────────────────────────────────────────────────────────────────

// Initializes bf_state_t
// also loads program
bf_state_t *init_state(char *filename);

// Checks if bs_state_t is still valid
// ie: if the tape_head or the pgm_head have overflowed
int is_state_valid(bf_state_t *s);

char* read_file(const char *filename, size_t *size);

// Get corresponding bracket
// Returns 0 if found, and sets head_pgm to found index
// Otherwise returns 1
int move_to_corresponding_bracket(bf_state_t *s);

// ─── Macros ──────────────────────────────────────────────────────────────────────────────────────

// Get char instruction pointed at by head
#define head_instr(s) s->pgm[s->pgm_head]

// Exits 1 and prints "UNIMPLEMENTED" to stderr
#define UNIMPLEMENTED {\
        fprintf(stderr, "This feature is currently unimplemented..."); \
        exit(1); \
    }
