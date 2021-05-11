#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "../lexer/lexer.h"
#include "../helpers.h"

#define MULTIPLE_SEP ','
#define END ';'

void parse_expression(token *tk)
{
    growable_buf param_buf_g;
    init_growable_buff(&param_buf_g, 256);

    node *new_node = malloc(sizeof new_node);
    new_node->name = tk->value;
    new_node->type = call_exp;

}

void parse(FILE *stream)
{
    token *curr_token;
    create_lexer(stream);
    while ((curr_token = get_token()) != NULL)
    {
        printf(curr_token->value);
    }
    free_lexer();
}