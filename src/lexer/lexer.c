#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "lexer.h"
#include "../helpers.h"

#define NEWLINE "\n"
#define OPERATORS "+-*/"
#define SPECIAL_CHARS "(){},;=:"
#define SYMBOLS_PATTERN "[a-zA-Z]"
#define NON_ASCII_PATTERN "[\x00-\x7F]"

token *append(token *head, char *src, int type)
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


void lex(FILE *cpl_file)
{
    regex_t symbol_regex;

    regcomp(&symbol_regex, SYMBOLS_PATTERN, 0);
    token *head = malloc(sizeof(token));
    char buf[2] = "\0";

    while ((buf[0] = fgetc(cpl_file)) != EOF)
    {
        if (strstr(NEWLINE, buf))
            continue;
        if (strstr(OPERATORS, buf))
            append(head, buf, operator);
        else if (strstr(SPECIAL_CHARS, buf))
            append(head, buf, special_char);
        else if (regexec(&symbol_regex, buf, 0, NULL, 0) == 0)
            printf(buf);
    };

    regfree(&symbol_regex);

    for (; head != NULL; head = head->next)
        printf(head->value);
}
