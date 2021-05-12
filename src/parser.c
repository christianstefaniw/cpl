#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "helpers.h"
#include "evaluator.h"

node *parse_expression(token *tk)
{
    node *curr_node = malloc(sizeof curr_node);

    while (tk->type != scol)
    {
        if (tk->type == number)
        {
            if (curr_node->left == NULL)
                curr_node->left = tk;
            else if (curr_node->right == NULL)
                curr_node->right = tk;
        }
        else if (tk->type == add)
        {
            curr_node->op = tk;
        }
        tk = get_token();
    }

    return curr_node;
}

void parse(FILE *stream)
{
    token *curr_token;
    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
    {
        eval(parse_expression(curr_token));
        free_token(curr_token);
    }
}