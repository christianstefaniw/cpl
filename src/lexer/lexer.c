#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "lexer.h"
#include "../helpers.h"

static FILE *file_stream;

static token_type get_ident_type(const char *ident_str)
{
    if (strcmp(ident_str, PRNT) == 0)
        return prnt;
    else if (strcmp(ident_str, FUNC) == 0)
        return func;

    return ident;
}

static token *append(token *head, char *src, token_type type)
{
    token *cursor;
    token *new_tk = malloc(sizeof(token));

    new_tk->value = strdup(src);
    new_tk->type = type;
    new_tk->next = NULL;

    if (head->value == NULL)
    {
        *head = *new_tk;
        return head;
    }

    cursor = head;

    while (cursor->next != NULL)
        cursor = cursor->next;

    cursor->next = new_tk;

    return new_tk;
}

static void get_ident(token *head)
{
    token_type tk_type;
    growable_buf ident_g;
    regex_t ascii_regex;
    regcomp(&ascii_regex, ASCII, 0);
    char char_buf[2] = "\0";

    init_growable_buff(&ident_g, 256);
    for (char_buf[0] = next_ch(); regexec(&ascii_regex, char_buf, 0, NULL, 0) == 0; char_buf[0] = next_ch())
        insert_growable_buff(&ident_g, char_buf[0]);

    tk_type = get_ident_type(ident_g.buffer);

    regfree(&ascii_regex);
    append(head, ident_g.buffer, tk_type);

    // go back 1 char in file because the for loop will read an
    // extra char that the main lex loop should read
    nav_back(-1L);
}

static void get_str_lit(token *head)
{
    char char_buf[2] = "\0";
    growable_buf str_g;

    init_growable_buff(&str_g, 256);
    for (char_buf[0] = next_ch(); strcmp(char_buf, D_QUOTE) != 0; char_buf[0] = next_ch())
        insert_growable_buff(&str_g, char_buf[0]);

    append(head, str_g.buffer, string);
}

static int next_ch()
{
    return fgetc(file_stream);
}

static void nav_back(long offset)
{
    fseek(file_stream, offset, SEEK_CUR);
}

token *lex(FILE *cpl_file)
{
    file_stream = cpl_file;

    regex_t numbers;

    regcomp(&numbers, NUMBER, 0);
    token *head = malloc(sizeof(token));
    char char_buf[2] = "\0";

    while ((char_buf[0] = next_ch()) != EOF)
    {
        if (isspace(char_buf[0]))
            continue;
        else if (strstr(SCOL, char_buf))
            append(head, char_buf, scol);
        else if (strstr(ADD, char_buf))
            append(head, char_buf, add);
        else if (strstr(LPAR, char_buf))
            append(head, char_buf, lpar);
        else if (strstr(RPAR, char_buf))
            append(head, char_buf, rpar);
        else if (regexec(&numbers, char_buf, 0, NULL, 0) == 0)
            append(head, char_buf, number);
        else if (strstr(D_QUOTE, char_buf))
            get_str_lit(head);
        else if (strstr(LBRACE, char_buf))
            append(head, char_buf, lbrace);
        else if (strstr(RBRACE, char_buf))
            append(head, char_buf, rbrace);
        else if (strstr(EQUAL, char_buf))
            append(head, char_buf, eq);
        else
        {
            // go back 1 char in file because the loop will read an
            // extra char that the ident loop should read
            nav_back(-1L);
            get_ident(head);
        }
    };

    fclose(file_stream);

    return head;
}
