typedef enum
{
    scol,
    prnt,
    ident,
    lpar,
    rpar,
    add,
    subtract,
    number,
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
#define IDENT "[a-zA-Z_]"

#define NEWLINE "\n"
#define D_QUOTE "\""

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
static token_type get_ident_type(const char *ident_str);
static token *new_token(token_type type, char *value);
static token *get_ident();
static token *get_str_lit();
static int next_ch();
static void nav_back(long offset);
token *get_token();
void free_token(token *tk);
