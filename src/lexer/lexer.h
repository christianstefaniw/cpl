typedef struct _token
{
    char *name;
    unsigned int value;
    struct _token *next;
} token;

void lex(FILE *cpl_file);
