enum
{
    scol,
    number,
    prnt,
    lpar,
    rpar,
    plus,
};

#define SCOL ";"
#define NUMBER "^[0-9]+$"
#define PRNT "print"
#define LPAR "("
#define RPAR ")"
#define PLUS "+"

typedef struct _token
{
    int type;
    char *value;
    struct _token *next;
} token;

void lex(FILE *cpl_file);
