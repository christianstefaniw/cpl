#include "lexer.h"

// todo fix enums
typedef enum
{
    call_exp,
} parsed_type;

typedef struct node
{
    token *left, *right, *op;
} node;

token *parse_token(token *tk);
node *parse_expression(token *tk);
void parse(FILE *stream);
