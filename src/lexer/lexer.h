typedef struct _token
{
    char *type;
    char value;
    struct _token *next;
} token;

void lex(FILE *cpl_file);
