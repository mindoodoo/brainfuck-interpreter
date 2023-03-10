/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdlib.h>

#define TAPE_SIZE 20000

// ─── Brainfuck State ─────────────────────────────────────────────────────────────────────────────

typedef byte unsigned char;

typedef struct bf_state_s {
    byte *tape;
    size_t tape_size;
} bf_state_t;

// Initializes empty tape
bf_state_t *init_tape(void);