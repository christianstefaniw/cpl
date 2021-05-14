#include "lexer.h"

#define PRNT "print"

typedef struct _node node;

typedef enum
{
    prnt,
} parsed_type;

typedef struct
{
    size_t cap;
    size_t len;
    node *nodes[];
} growable_nodes_arr;

typedef struct _node
{
    token *value;
    growable_nodes_arr *children;
} node;

node *parse_expression(token *tk);
void *parse_fn_dec(token *tk);
node *parse_token(token *tk);
void parse(FILE *stream);
void init_growable_nodes_arr(growable_nodes_arr *arr, size_t cap);
void insert_growable_nodes_arr(growable_nodes_arr *arr, node *elem);
void free_growable_nodes_arr(growable_nodes_arr *arr);
