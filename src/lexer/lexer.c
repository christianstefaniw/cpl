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
    regex_t ascii_regex;
    regcomp(&ascii_regex, ASCII, 0);
    char buf[2] = "\0";

    // todo make buffer helper funcs like expand and stuff
    char identifier[256] = "";
    for (buf[0] = next_ch(); regexec(&ascii_regex, buf, 0, NULL, 0) == 0; buf[0] = next_ch())
        strcat(identifier, buf);

    tk_type = get_ident_type(identifier);

    regfree(&ascii_regex);
    append(head, identifier, tk_type);

    // go back 1 char in file because the for loop will read an
    // extra char that the main lex loop should read
    nav_back(-1L);
}

static void get_str_lit(token *head)
{
    char buf[2] = "\0";

    // todo make buffer helper funcs like expand and stuff
    char str[256] = "";
    for (buf[0] = next_ch(); strcmp(buf, D_QUOTE) != 0; buf[0] = next_ch())
    {
        strcat(str, buf);
    }
    append(head, str, string);
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
    char buf[2] = "\0";
    
    while ((buf[0] = next_ch()) != EOF)
    {
        if (isspace(buf[0]))
            continue;
        else if (strstr(SCOL, buf))
            append(head, buf, scol);
        else if (strstr(ADD, buf))
            append(head, buf, add);
        else if (strstr(LPAR, buf))
            append(head, buf, lpar);
        else if (strstr(RPAR, buf))
            append(head, buf, rpar);
        else if (regexec(&numbers, buf, 0, NULL, 0) == 0)
            append(head, buf, number);
        else if (strstr(D_QUOTE, buf))
            get_str_lit(head);
        else if (strstr(LBRACE, buf))
            append(head, buf, lbrace);
        else if (strstr(RBRACE, buf))
            append(head, buf, rbrace);
        else if (strstr(EQUAL, buf))
            append(head, buf, eq);
        else
        {
            // go back 1 char in file because the loop will read an
            // extra char that the ident loop should read
            nav_back(-1L);
            get_ident(head);
        }
    };

    fclose(file_stream);

    for (; head != NULL; head = head->next)
    {
        printf("type: %i, value: %s\n", head->type, head->value);
    }

    return head;
}
