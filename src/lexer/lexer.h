enum
{
    null = 0,
    operator,
    special_char,
    str,
    symbol,
    number,
};

typedef struct _identifier
{
    int token;
    char *value;
    struct _identifier *next;
} identifier;

void lex(FILE *cpl_file);
