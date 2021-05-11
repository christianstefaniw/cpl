#include "lexer.h"

// todo fix enums
typedef enum
{
    call_exp,
    str_lit,
    num_lit,
    eol,
} parsed_type;

typedef struct _node
{
    parsed_type type;
    char *value;
    struct _node *param;
} node;

void *init_node(node *new_node, token *tk, token_type tk_type);
node *parse_expression(token *tk);
node *parse_str_lit(token *tk);
node *parse_num_lit(token *tk);
node *parse_token(token *tk);
void parse(FILE *stream);
