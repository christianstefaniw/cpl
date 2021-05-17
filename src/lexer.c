
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
    _lxr->curr_char_buf[1] = '\0';
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

token *new_token(token_type type, char *value)
{
    token *new_tk = malloc(sizeof new_tk);
    new_tk->type = type;
    new_tk->value = value;
    return new_tk;
}

static token *get_ident()
{
    token_type tk_type;
    regex_t regex;
    token *tk;
    growable_buf ident_g;
    char curr_char, peeked_char;

    regcomp(&regex, IDENT, 0);
    init_growable_buff(&ident_g, 256);

    for (curr_char = peek_ch(); regexec(&regex, &curr_char, 0, NULL, 0) == 0; curr_char = peek_ch())
    {
        insert_growable_buff(&ident_g, curr_char);
        curr_char = next_ch();
    }

    peeked_char = peek_ch();
    tk_type = get_ident_type(ident_g.buffer, peeked_char);
    return new_token(tk_type, ident_g.buffer);
}

static token_type get_ident_type(char *tk_value, char next_char)
{
    if (strcmp(tk_value, FN_DEC) == 0)
        return fn_dec;
    else if (strcmp(&next_char, LPAR) == 0)
        return fn_call;
    else if (strcmp(&next_char, ASSIGN) == 0)
        return assign;
    else
        return ident;
}

static token *get_num_lit()
{
    char curr_num;
    growable_buf num_g;

    init_growable_buff(&num_g, 256);
    for (curr_num = peek_ch(); isdigit(curr_num); curr_num = peek_ch())
    {
        insert_growable_buff(&num_g, curr_num);
        curr_num = next_ch();
    }

    return new_token(number, num_g.buffer);
}

static token *get_str_lit()
{
    char curr_char;
    growable_buf str_g;

    init_growable_buff(&str_g, 256);
    for (curr_char = next_ch(); curr_char != D_QUOTE[0]; curr_char = next_ch())
    {
        if (curr_char == EOL)
        {
            fprintf(stderr, "syntax error: missing closing quote(\")\n");
            exit(1);
        }
        insert_growable_buff(&str_g, curr_char);
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
        else if (strcmp(SCOL, _lxr->curr_char_buf) == 0)
            return new_token(scol, _lxr->curr_char_buf);
        else if (strcmp(ADD, _lxr->curr_char_buf) == 0)
            return new_token(add, _lxr->curr_char_buf);
        else if (strcmp(LPAR, _lxr->curr_char_buf) == 0)
            return new_token(lpar, _lxr->curr_char_buf);
        else if (strcmp(RPAR, _lxr->curr_char_buf) == 0)
            return new_token(rpar, _lxr->curr_char_buf);
        else if (isdigit(_lxr->curr_char_buf[0]))
        {
            nav_back(-1L);
            return get_num_lit();
        }
        else if (strcmp(D_QUOTE, _lxr->curr_char_buf) == 0)
            return get_str_lit();
        else if (strcmp(LBRACE, _lxr->curr_char_buf) == 0)
            return new_token(lbrace, _lxr->curr_char_buf);
        else if (strcmp(ASSIGN, _lxr->curr_char_buf) == 0)
            return new_token(assign, _lxr->curr_char_buf);
        else if (strcmp(RBRACE, _lxr->curr_char_buf) == 0)
            return new_token(rbrace, _lxr->curr_char_buf);
        else if (strcmp(EQUAL, _lxr->curr_char_buf) == 0)
            return new_token(eq, _lxr->curr_char_buf);
        else if (strcmp(ADD, _lxr->curr_char_buf) == 0)
            return new_token(add, _lxr->curr_char_buf);
        else if (strcmp(MUL, _lxr->curr_char_buf) == 0)
            return new_token(mul, _lxr->curr_char_buf);
        else if (strcmp(SUBT, _lxr->curr_char_buf) == 0)
            return new_token(subt, _lxr->curr_char_buf);
        else if (strcmp(DIVI, _lxr->curr_char_buf) == 0)
            return new_token(divi, _lxr->curr_char_buf);
        else
        {
            nav_back(-1L);
            return get_ident();
        }
    };

    clean_lexer();

    return NULL;
}