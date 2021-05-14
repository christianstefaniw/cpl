#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "helpers.h"
#include "evaluator.h"

void parse_expression(token *tk)
{
}

void parse_fn_dec(token *tk)
{
}

node *parse_fn_call(token *tk)
{
    token *curr_token;

    node *fn_node = malloc(sizeof fn_node);
    growable_nodes_arr *fn_params = malloc(sizeof fn_params);

    init_growable_nodes_arr(fn_params, 8);

    while (get_token()->type != lpar)
    {
        continue;
    }

    while ((curr_token = get_token())->type != rpar)
    {
        node *param_node = malloc(sizeof param_node);
        param_node->value = curr_token;
        insert_growable_nodes_arr(fn_params, param_node);
    }

    fn_node->children = fn_params;

    return fn_node;
}

void parse_token(token *tk, node *root)
{
    growable_nodes_arr *next_level = malloc(sizeof next_level);
    init_growable_nodes_arr(next_level, 5);

    if (tk->type == fn_call)
    {
        root->value = tk;
        insert_growable_nodes_arr(next_level, parse_fn_call(tk));
        root->children = next_level;
    }
}

void parse(FILE *stream)
{
    node *root = malloc(sizeof root);
    token *curr_token;
    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
        parse_token(curr_token, root);

    eval(root);
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
