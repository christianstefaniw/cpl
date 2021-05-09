typedef enum
{
    scol,
    number,
    ident,
    lpar,
    rpar,
    plus,
    string,
} TokenType;

static inline char *string_from_tkn_type(TokenType type)
{
    static const char *strings[] = {"scol",
                                    "number",
                                    "ident",
                                    "lpar",
                                    "rpar",
                                    "plus",
                                    "string"};

    return (char *)strings[type];
}

#define SCOL ";"
#define NUMBER "^[0-9]$"
#define PRNT "print"
#define LPAR "("
#define RPAR ")"
#define PLUS "+"
#define NEWLINE "\n"
#define ASCII "[a-zA-Z]"
#define D_QUOTE "\""

typedef struct _token
{
    TokenType type;
    char *value;
    struct _token *next;
} token;

static token *append(token *head, char *src, TokenType type);
static void get_ident(token *head);
static void get_str_lit(token *head);
static inline int next_ch();
static inline void nav_back(long offset);
void lex(FILE *cpl_file);
