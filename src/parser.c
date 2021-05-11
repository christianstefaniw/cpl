#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "helpers.h"
#include "evaluator.h"

void *init_node(node *new_node, token *tk, token_type tk_type)
{
    new_node->value = tk->value;
    new_node->type = tk_type;
}

node *parse_expression(token *tk)
{
    growable_buf param_buf_g;
    init_growable_buff(&param_buf_g, 256);
    node *exp_node = malloc(sizeof exp_node);
    init_node(exp_node, tk, call_exp);

    while ((tk = get_token())->type != rpar)
    {
        exp_node->param = parse_token(tk);
        free_token(tk);
    }
    return exp_node;
}

node *parse_str_lit(token *tk)
{
    node *str_node = malloc(sizeof str_node);
    init_node(str_node, tk, str_lit);
    return str_node;
}

node *parse_num_lit(token *tk)
{
    node *num_node = malloc(sizeof num_node);
    init_node(num_node, tk, num_lit);
    return num_node;
}

node *parse_eol(token *tk)
{
    node *scol_node = malloc(sizeof scol_node);
    init_node(scol_node, tk, eol);
    return scol_node;
}

node *parse_token(token *tk)
{
    switch (tk->type)
    {
    case (prnt):
        return parse_expression(tk);
    case (number):
        return parse_num_lit(tk);
    case (string):
        return parse_str_lit(tk);
    case (scol):
        return parse_eol(tk);
    }
}

void parse(FILE *stream)
{
    token *curr_token;
    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
    {
        eval(parse_token(curr_token));
        free_token(curr_token);
    }
}