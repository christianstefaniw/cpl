enum
{
    operator,
    special_char,
    str,
    symbol,
    number,
};

typedef struct _token
{
    int type;
    char *value;
    struct _token *next;
} token;

void lex(FILE *cpl_file);
