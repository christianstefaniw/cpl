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

identifier *append(identifier *head, char *src, int token)
{
    identifier *cursor;
    identifier *new_id = malloc(sizeof(identifier));

    new_id->value = strdup(src);
    new_id->token = token;
    new_id->next = NULL;

    if (head->token == null)
    {
        *head = *new_id;
        return head;
    }

    cursor = head;

    while (cursor->next != NULL)
        cursor = cursor->next;

    cursor->next = new_id;

    return new_id;
}

void lex(FILE *cpl_file)
{
    regex_t symbol_regex;

    regcomp(&symbol_regex, SYMBOLS_PATTERN, 0);
    identifier *head = malloc(sizeof(identifier));
    char buf[2] = "\0";

    while ((buf[0] = fgetc(cpl_file)) != EOF)
    {
        if (strstr(NEWLINE, buf))
            continue;
        if (strstr(OPERATORS, buf))
            append(head, buf, operator);
        else if (strstr(SPECIAL_CHARS, buf))
            append(head, buf, special_char);
    };

    regfree(&symbol_regex);

    for (; head != NULL; head = head->next)
        printf(head->value);
}
