/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#pragma once

#include <stdlib.h>

// ─── Abstract Syntaxe Tree ───────────────────────────────────────────────────────────────────────

// Possible brainfuck ast variations
enum Ast {
    MoveRight,
    MoveLeft,
    Increment,
    Decrement,
    Output,
    Input,
    Loop
};

// Structure describing the abstract syntaxe tree we parse into
typedef struct ast_node_s {
    enum Ast type;
    ast_node_t *next;           // Null terminated
    ast_node_t *loop_content;   // If loop, NULL terminated array of nodes
} ast_node_t;

    // ─── Ast Functions ───────────────────────────────────────────────────────────────────────

// Parses

// ─── Utilities ───────────────────────────────────────────────────────────────────────────────────

char* read_file(const char *filename, size_t *size);