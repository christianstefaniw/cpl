#include "lexer.h"

#define PRNT "print"

typedef enum
{
    prnt,
} parsed_type;

typedef struct expression_node
{
    token *left, *right, *op;
} expression_node;


expression_node *parse_token(token *tk);
expression_node *parse_expression(token *tk);
void *parse_fn_call(token *tk);
void parse(FILE *stream);
