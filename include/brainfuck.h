/*
 * Created on Fri Mar 10 2023
 *
 * by Léon Sautour
 */

#pragma once

#include <stdlib.h>
#include <llvm-c/Core.h>

#define TAPE_LENGTH 20000

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
    struct ast_node_s *loop_content;   // If loop, Ast linked list of contents
} ast_node;

    // ─── Ast Functions ───────────────────────────────────────────────────────────────────────

// Parses file contents into an AST
ast_node *parse_tokens(char *content, size_t size);

// Parses loop content into AST
ast_node *parse_loop(char *content, size_t *index, size_t size);

// Parses token (char) into single AST struct instance (allocated)
ast_node *parse_token(char token);

// ─── Codegen ─────────────────────────────────────────────────────────────────────────────────────

// Build module (codegen entry point)
LLVMModuleRef build_module(ast_node *ast_head);

// Create global variable for tape
void build_state(LLVMModuleRef mod, LLVMBuilderRef builder);

// Build internal library
// (This is essentially each brainfuck function)
int build_internal_lib(LLVMModuleRef mod);

    // ─── Internal Library Factories ──────────────────────────────────────────────────────────

// One per token
void move_left(LLVMModuleRef mod, LLVMBuilderRef builder);
void move_right(LLVMModuleRef mod, LLVMBuilderRef builder);
void increment(LLVMModuleRef mod, LLVMBuilderRef builder);
void decrement(LLVMModuleRef mod, LLVMBuilderRef builder);
void output(LLVMModuleRef mod, LLVMBuilderRef builder);
void input(LLVMModuleRef mod, LLVMBuilderRef builder);
void loop_open(LLVMModuleRef mod, LLVMBuilderRef builder);
void loop_close(LLVMModuleRef mod, LLVMBuilderRef builder);


// ─── Utilities ───────────────────────────────────────────────────────────────────────────────────

char* read_file(const char *filename, size_t *size);