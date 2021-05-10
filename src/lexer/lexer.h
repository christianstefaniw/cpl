#include <stdio.h>

typedef enum
{
    scol,
    prnt,
    number,
    ident,
    lpar,
    rpar,
    add,
    subtract,
    string,
    eq,
    func,
    lbrace,
    rbrace,
    comma,

} token_type;


#define SCOL ";"
#define NUMBER "^[0-9]$"
#define PRNT "print"
#define LPAR "("
#define RPAR ")"
#define ADD "+"
#define SUBTRACT "-"
#define EQUAL "="
#define FUNC "fn"
#define LBRACE "{"
#define RBRACE "}"
#define COMMA ","

#define NEWLINE "\n"
#define ASCII "[a-zA-Z]"
#define D_QUOTE "\""

typedef struct _token
{
    token_type type;
    char *value;
    struct _token *next;
} token;

static token_type get_ident_type(const char *ident_str);
static token *append(token *head, char *src, token_type type);
static void get_ident(token *head);
static void get_str_lit(token *head);
static int next_ch();
static void nav_back(long offset);
token *lex(FILE *cpl_file);
