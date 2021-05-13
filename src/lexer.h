typedef enum
{
    scol,
    fn_call,
    ident,
    lpar,
    rpar,
    add,
    mul,
    subt,
    divi,
    number,
    string,
    eq,
    lbrace,
    rbrace,
    comma,
} token_type;

typedef enum
{
    peek,
    no_peek,
} should_peek;

#define SCOL ";"
#define NUMBER "^[0-9]$"
#define LPAR "("
#define RPAR ")"
#define ADD "+"
#define SUBT "-"
#define EQUAL "="
#define FUNC "fn"
#define LBRACE "{"
#define RBRACE "}"
#define COMMA ","
#define MUL "*"
#define DIVI "/"
#define IDENT "[a-zA-Z_]"

#define NEWLINE "\n"
#define D_QUOTE "\""
#define MULTIPLE_SEP ','
#define EOL ';'

typedef struct _lexer
{
    FILE* stream;
    char curr_char_buf[1];
} lexer;

typedef struct _token
{
    token_type type;
    char *value;
} token;

void init_lexer(FILE *stream);
void free_lexer();
static token *new_token(token_type type, char *value);
static token *get_ident();
static token *get_str_lit();
static int next_ch();
static void nav_back(long offset);
token *get_token(should_peek p);
void free_token(token *tk);
char peek_ch();
