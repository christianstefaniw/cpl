#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "errors.h"
#include "parser.h"
#include "helpers.h"
#include "evaluator.h"

void parse_expression(token *tk)
{
}

node *parse_fn_dec(token *tk)
{
    token *curr_token;

    node *fn_dec_node = malloc(sizeof fn_dec_node);
    growable_nodes_arr *fn = malloc(sizeof fn);

    init_growable_nodes_arr(fn, 8);

    while (get_token()->type != lbrace)
        continue;

    while ((curr_token = get_token())->type != rbrace)
    {
        node *fn_line = malloc(sizeof fn_line);
        fn_line = parse_token(curr_token);
        insert_growable_nodes_arr(fn, fn_line);
    }

    // add right brace
    insert_growable_nodes_arr(fn, parse_token(curr_token));

    fn_dec_node->value = tk;
    fn_dec_node->children = fn;

    return fn_dec_node;
}

node *parse_fn_call(token *tk)
{
    token *curr_token;

    node *fn_node = malloc(sizeof fn_node);
    growable_nodes_arr *fn_params = malloc(sizeof fn_params);

    init_growable_nodes_arr(fn_params, 8);

    while (get_token()->type != fn_call)
        continue;

    while ((curr_token = get_token())->type != scol)
    {

        check_semicolon_error(curr_token->type);

        node *param_node = malloc(sizeof param_node);
        param_node = parse_token(curr_token);
        insert_growable_nodes_arr(fn_params, param_node);
    }

    fn_node->value = tk;
    fn_node->children = fn_params;

    return fn_node;
}

node *parse_assign(token *tk)
{
    token *curr_token;

    node *assign_node = malloc(sizeof assign_node);
    growable_nodes_arr *rval = malloc(sizeof rval);

    init_growable_nodes_arr(rval, 8);

    while ((curr_token = get_token())->type != scol)
    {
        if (curr_token->type == assign)
            continue;

        check_semicolon_error(curr_token->type);

        node *rval_node = malloc(sizeof rval_node);
        rval_node = parse_token(curr_token);
        insert_growable_nodes_arr(rval, rval_node);
    }

    assign_node->value = tk;
    assign_node->children = rval;

    return assign_node;
}

node *parse_generic(token *tk)
{
    node *gen_node = malloc(sizeof gen_node);
    gen_node->value = tk;
    return gen_node;
}

node *parse_token(token *tk)
{
    if (tk->type == fn_call)
        return parse_fn_call(tk);
    else if (tk->type == assign)
        return parse_assign(tk);
    else if (tk->type == fn_dec)
        return parse_fn_dec(tk);
    else
        return parse_generic(tk);
}

void parse(FILE *stream)
{
    token *curr_token;
    node *curr_node;

    node *program = malloc(sizeof program);
    growable_nodes_arr *lines = malloc(sizeof lines);
    init_growable_nodes_arr(lines, 10);

    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
    {
        curr_node = parse_token(curr_token);
        insert_growable_nodes_arr(lines, curr_node);
    }

    program->children = lines;

    eval(program);
}

void init_growable_nodes_arr(growable_nodes_arr *arr, size_t cap)
{
    arr->nodes = malloc(cap * sizeof(arr->nodes));
    arr->cap = cap;
    arr->len = 0;
}

void insert_growable_nodes_arr(growable_nodes_arr *arr, node *elem)
{
    if (arr->len == arr->cap)
    {
        arr->cap *= 2;
        arr->nodes = realloc(arr->nodes, arr->cap * sizeof(arr->nodes));
    }
    arr->nodes[arr->len++] = elem;
}

void free_growable_nodes_arr(growable_nodes_arr *arr)
{
    free(arr);
}
