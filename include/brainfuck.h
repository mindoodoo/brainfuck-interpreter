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
    struct ast_node_s *next;           // Null terminated
    struct ast_node_s *loop_content;   // If loop, NULL terminated array of nodes
} ast_node_t;

    // ─── Ast Functions ───────────────────────────────────────────────────────────────────────

// Parses file contents into an AST
ast_node_t *parse_tokens(char *content, size_t size);

// Parses loop content into AST
ast_node_t *parse_loop(char *content, size_t *index, size_t size);

// Parses token (char) into single AST struct instance (allocated)
ast_node_t *parse_token(char token);

// ─── Utilities ───────────────────────────────────────────────────────────────────────────────────

char* read_file(const char *filename, size_t *size);