/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include "brainfuck.h"

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
            if (s->tape_head == 0)
                return HEAD_OVERFLOW;
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
            printf("%c", s->tape[s->tape_head]);
            s->pgm_head++;
            break;
        case ',':
            byte c = 0;
            if ((c = getc(stdin)) == EOF)
                c = 0;
            s->tape[s->tape_head] = c;
            s->pgm_head++;
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

// Runs program loaded into state
int run_state(bf_state_t *s) {
    int output = 0;

    while (!(output = is_state_valid(s)))
        if ((output = run_head(s)))
            break;
    return output;
}