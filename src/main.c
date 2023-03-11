/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include "brainfuck.h"

char *check_args(int ac, char **av) {
    if (ac != 2) {
        fprintf(stderr, "Invalid number of arguments...");
        return NULL;
    }
    return av[1];
}

int main(int ac, char **av) {
    char *filename;

    if (!(filename = check_args(ac, av)))
        return 1;
    return 0;
}