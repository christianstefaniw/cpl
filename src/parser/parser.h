typedef enum
{
    call_exp,
    str_lit,
} parsed_type;

typedef struct _param
{
    char *value;
    struct _param *next;
} param;

typedef struct _node
{
    parsed_type type;
    char *name;
    struct node *left, *right;
} node;

void next_exression();
void parse();
