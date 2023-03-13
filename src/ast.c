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
    ast_node_t *last = NULL;
    ast_node_t *temp = NULL;

    for (size_t i = 0; i < size; i++) {
        if (!(temp = parse_token(content[i])))
            continue;
        if (temp->type == Loop) {
            // Attempt to parse loop content and set it
            if (!(temp->loop_content = parse_loop(content, &i, size)))
                return NULL;
        }

        // Link to head and replace head
        if (head) {
            last->next = temp;
            last = temp;
        } else {
            head = temp;
            last = temp;
        }
    }

    return head;
}

// Parses loop content into AST
ast_node_t *parse_loop(char *content, size_t *index, size_t size) {
    ast_node_t *head = NULL;
    ast_node_t *last = NULL;
    ast_node_t *temp = NULL;
    int opening_count = 1;
    int closing_count = 0;

    (*index)++;

    // This will also increment the index of the caller
    for (;*index < size; (*index)++) {
        // Scope tracking
        if (content[*index] == ']') {
            if (closing_count + 1 == opening_count)
                break;
            else
                closing_count++;
        } else if (content[*index] == '[')
            opening_count++;

        // Attempt to parse
        if (!(temp = parse_token(content[*index])))
            continue;

        // Parse loop
        if (temp->type == Loop) {
            if (!(temp->loop_content = parse_loop(content, index, size)))
                return NULL;
            else
                closing_count++;
        }

        // Link
        if (head) {
            last->next = temp;
            last = temp;
        } else {
            head = temp;
            last = temp;
        }
    }

    return head;
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
