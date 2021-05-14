#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "helpers.h"
#include "evaluator.h"

node *parse_expression(token *tk)
{
    
}

void *parse_fn_dec(token *tk)
{
}

node *parse_token(token *tk)
{
    if (tk->type == number)
        return parse_expression(tk);
}

void parse(FILE *stream)
{
    token *curr_token;
    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
    {
        printf("type: %i, value: %s\n", curr_token->type, curr_token->value);
        // node *parsed_token = parse_token(curr_token);
        // eval(parsed_token);
    }
}

void init_growable_nodes_arr(growable_nodes_arr *arr, size_t cap)
{
    *(arr->nodes) = malloc(cap * sizeof(*(arr->nodes)));
    arr->cap = cap;
    arr->len = 0;
}

void insert_growable_nodes_arr(growable_nodes_arr *arr, node *elem)
{
    if (arr->len == arr->cap)
    {
        arr->cap *= 2;
        *(arr->nodes) = realloc(arr->nodes, arr->cap * sizeof(*(arr->nodes)));
    }
    arr->nodes[arr->len++] = elem;
}

void free_growable_nodes_arr(growable_nodes_arr *arr)
{
    free(arr);
}
