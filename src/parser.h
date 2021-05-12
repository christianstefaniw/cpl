#include "lexer.h"

// todo fix enums
typedef enum
{
    call_exp,
} parsed_type;

typedef struct _expr_node
{
    token *left, *right, *op;
} expr_node;

token *parse_token(token *tk);
token *parse_expression(token *tk);
void parse(FILE *stream);
