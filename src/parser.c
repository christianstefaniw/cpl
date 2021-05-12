#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "helpers.h"
#include "evaluator.h"


expr_node *parse_equation(){}

token *parse_token(token *tk)
{
    switch (tk->type)
    {
        case(lpar):
            parse_expression(tk);
    }
}

token *parse_expression(token *tk)
{
    
}

void parse(FILE *stream)
{
    token *curr_token;
    init_lexer(stream);

    while ((curr_token = get_token()) != NULL)
    {
        printf("%s\n", curr_token->value);
        eval(parse_expression(curr_token));
        free_token(curr_token);
    }
}