#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "lexer.h"
#include "../helpers.h"

static lexer *lxr;

void create_lexer(FILE *stream)
{
    lxr = malloc(sizeof lxr);
    lxr->stream = stream;
}

void free_lexer()
{
    free(lxr);
}

static token_type get_ident_type(const char *ident_str)
{
    if (strcmp(ident_str, PRNT) == 0)
        return prnt;
    else if (strcmp(ident_str, FUNC) == 0)
        return func;

    return ident;
}

static token *new_token(token_type type, char *value)
{
    token *new_tk = malloc(sizeof new_tk);
    new_tk->type = type;
    new_tk->value = value;
    return new_tk;
}

static token *get_ident()
{
    token_type tk_type;
    growable_buf ident_g;
    regex_t ident_reg;

    regcomp(&ident_reg, IDENT, 0);
    char char_buf[2] = "\0";

    init_growable_buff(&ident_g, 256);

    for (char_buf[0] = next_ch(); regexec(&ident_reg, char_buf, 0, NULL, 0) == 0; char_buf[0] = next_ch())
        insert_growable_buff(&ident_g, char_buf[0]);

    tk_type = get_ident_type(ident_g.buffer);
    regfree(&ident_reg);

    nav_back(-1L);

    return new_token(tk_type, ident_g.buffer);
}

static token *get_str_lit()
{
    char char_buf[2] = "\0";
    growable_buf str_g;

    init_growable_buff(&str_g, 256);
    for (char_buf[0] = next_ch(); strcmp(char_buf, D_QUOTE) != 0; char_buf[0] = next_ch())
        insert_growable_buff(&str_g, char_buf[0]);

    return new_token(string, str_g.buffer);
}

static int next_ch()
{
    return fgetc(lxr->stream);
}

static void nav_back(long offset)
{
    fseek(lxr->stream, offset, SEEK_CUR);
}

token *get_token()
{
    regex_t numbers;

    regcomp(&numbers, NUMBER, 0);
    char char_buf[2] = "\0";

    while ((char_buf[0] = next_ch()) != EOF)
    {
        if (isspace(char_buf[0]))
            continue;
        else if (strstr(SCOL, char_buf))
            return new_token(scol, char_buf);
        else if (strstr(ADD, char_buf))
            return new_token(add, char_buf);
        else if (strstr(LPAR, char_buf))
            return new_token(lpar, char_buf);
        else if (strstr(RPAR, char_buf))
            return new_token(rpar, char_buf);
        else if (regexec(&numbers, char_buf, 0, NULL, 0) == 0)
            return new_token(number, char_buf);
        else if (strstr(D_QUOTE, char_buf))
            return get_str_lit();
        else if (strstr(LBRACE, char_buf))
            return new_token(lbrace, char_buf);
        else if (strstr(RBRACE, char_buf))
            return new_token(rbrace, char_buf);
        else if (strstr(EQUAL, char_buf))
            return new_token(eq, char_buf);
        else
        {
            nav_back(-1L);
            return get_ident();
        }
    };

    fclose(lxr->stream);

    return NULL;
}
