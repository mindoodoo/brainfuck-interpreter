/*
 * Created on Mon Mar 13 2023
 *
 * by Léon Sautour
 */

#include <stdio.h>
#include "brainfuck.h"

// Parses file contents into an AST
ast_node_t *parse_tokens(char *content, size_t size) {
    ast_node_t *head = NULL;
    ast_node_t *temp = NULL;
    ast_node_t *loop_temp = NULL;
    
    for (size_t i = 0; i < size; i++) {
        if (!(temp = parse_token(content[i])))
            continue;
        if (temp->type == Loop) {
            // Attempt to parse loop content and set it
            if (!(loop_temp = parse_loop(content, &i, size)))
                return NULL;
            temp->loop_content = loop_temp;
        }
        // Link to head and replace head
        head->next = temp;
        head = temp;
    }
}

// Parses loop content into AST
ast_node_t *parse_loop(char *content, size_t *index, size_t size) {

}

// Parses token (char) into single AST struct instance (allocated)
ast_node_t *parse_token(char token) {
    ast_node_t *output = calloc(1, sizeof(ast_node_t));
    
    switch (token) {
        case '>':
            output->type = MoveRight;
            break;
        case '<':
            output->type = MoveLeft;
            break;
        case '+':
            output->type = Increment;
            break;
        case '-':
            output->type = Decrement;
            break;
        case '.':
            output->type = Output;
            break;
        case ',':
            output->type = Input;
            break;
        case '[':
            output->type = Loop;
            break;
        case ']':
            fprintf(stderr, "This should not happen. Encountered wild ']' !!");
            free(output);
            output = NULL;
        default:
            free(output);
            output = NULL;
            break;
    }
    return output;
}
