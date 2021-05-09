typedef enum
{
    scol,
    number,
    ident,
    lpar,
    rpar,
    plus,
} TokenType;

#define SCOL ";"
#define NUMBER "^[0-9]$"
#define PRNT "print"
#define LPAR "("
#define RPAR ")"
#define PLUS "+"
#define NEWLINE "\n"
#define ASCII "[a-zA-Z]"

typedef struct _token
{
    TokenType type;
    char *value;
    struct _token *next;
} token;

static void nav_back(long offset);
static token *append(token *head, char *src, TokenType type);
TokenType get_ident(token *head);
int next_ch();
void lex(FILE *cpl_file);
