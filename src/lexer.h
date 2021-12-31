typedef enum
{
    scol,
    fn_dec,
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
    fn_call,
    lbrace,
    rbrace,
    comma,
    assign,
    comment,
    newline,
} token_type;

#define SCOL ";"
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
#define FN_DEC "$"
#define ASSIGN "="
#define FN_CALL "@"
#define COMMENT "#"

#define NEWLINE "\n"
#define D_QUOTE "\""
#define EOL ';'

typedef struct
{
    FILE *stream;
    char curr_char_buf[1];
} lexer;

typedef struct
{
    token_type type;
    char *value;
} token;

void init_lexer(FILE *stream);
void free_lexer();
token *new_token(token_type type, char *value);
static token *get_comment();
static token *get_ident();
static token *get_str_lit();
static char next_ch();
static void nav_back(long offset);
token *get_token();
void free_token(token *tk);
char peek_ch();
static token_type get_ident_type(char *tk_value, char next_char);