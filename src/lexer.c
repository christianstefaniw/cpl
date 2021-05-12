
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "lexer.h"
#include "helpers.h"

static lexer *_lxr;

void init_lexer(FILE *stream)
{
    _lxr = malloc(sizeof _lxr);
    _lxr->stream = stream;
    _lxr->curr_char_buf[2] = '\0';
}

void clean_lexer()
{
    fclose(_lxr->stream);
    free(_lxr);
}

void free_token(token *tk)
{
    free(tk);
}

static token_type get_ident_type(const char *ident_str)
{
    if (strcmp(ident_str, PRNT) == 0)
        return prnt;

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

    for (char_buf[0] = peek_ch(); regexec(&ident_reg, char_buf, 0, NULL, 0) == 0; char_buf[0] = peek_ch())
    {
        insert_growable_buff(&ident_g, char_buf[0]);
        char_buf[0] = next_ch();
    }

    tk_type = get_ident_type(ident_g.buffer);
    regfree(&ident_reg);

    return new_token(tk_type, ident_g.buffer);
}

static token *get_num_lit()
{
    char num_buf[2] = "\0";
    growable_buf num_g;

    init_growable_buff(&num_g, 256);
    for (num_buf[0] = peek_ch(); isdigit(num_buf[0]); num_buf[0] = peek_ch())
    {
        insert_growable_buff(&num_g, num_buf[0]);
        num_buf[0] = next_ch();
    }

    return new_token(number, num_g.buffer);
}

static token *get_str_lit()
{
    char char_buf[2] = "\0";
    growable_buf str_g;

    init_growable_buff(&str_g, 256);
    for (char_buf[0] = next_ch(); strcmp(char_buf, D_QUOTE) != 0; char_buf[0] = next_ch())
    {
        if (char_buf[0] == EOL)
        {
            fprintf(stderr, "syntax error: missing closing quote(\")\n");
            exit(1);
        }
        insert_growable_buff(&str_g, char_buf[0]);
    }

    return new_token(string, str_g.buffer);
}

static int next_ch()
{
    return fgetc(_lxr->stream);
}

static void nav_back(long offset)
{
    fseek(_lxr->stream, offset, SEEK_CUR);
}

char peek_ch()
{
    int c;

    c = fgetc(_lxr->stream);
    ungetc(c, _lxr->stream);

    return c;
}

token *get_token()
{
    while ((_lxr->curr_char_buf[0] = next_ch()) != EOF)
    {
        if (isspace(_lxr->curr_char_buf[0]))
            continue;
        else if (strstr(SCOL, _lxr->curr_char_buf))
            return new_token(scol, _lxr->curr_char_buf);
        else if (strstr(ADD, _lxr->curr_char_buf))
            return new_token(add, _lxr->curr_char_buf);
        else if (strstr(LPAR, _lxr->curr_char_buf))
            return new_token(lpar, _lxr->curr_char_buf);
        else if (strstr(RPAR, _lxr->curr_char_buf))
            return new_token(rpar, _lxr->curr_char_buf);
        else if (isdigit(_lxr->curr_char_buf[0]))
        {
            nav_back(-1L);
            return get_num_lit();
        }
        else if (strstr(D_QUOTE, _lxr->curr_char_buf))
            return get_str_lit();
        else if (strstr(LBRACE, _lxr->curr_char_buf))
            return new_token(lbrace, _lxr->curr_char_buf);
        else if (strstr(RBRACE, _lxr->curr_char_buf))
            return new_token(rbrace, _lxr->curr_char_buf);
        else if (strstr(EQUAL, _lxr->curr_char_buf))
            return new_token(eq, _lxr->curr_char_buf);
        else if (strstr(ADD, _lxr->curr_char_buf))
            return new_token(add, _lxr->curr_char_buf);
        else
        {
            nav_back(-1L);
            return get_ident();
        }
    };

    clean_lexer();

    return NULL;
}