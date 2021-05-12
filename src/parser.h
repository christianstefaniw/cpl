#include "lexer.h"

#define PRNT "print"

typedef enum
{
    prnt,
} parsed_type;

typedef struct node
{
    token *left, *right, *op;
} node;

node *parse_token(token *tk);
node *parse_expression(token *tk);
node *parse_fn_call(token *tk);
void parse(FILE *stream);
