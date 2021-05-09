#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "lexer.h"
#include "../helpers.h"

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
    token *head = malloc(sizeof(token));
    char buf[2] = "\0";

    while ((buf[0] = fgetc(cpl_file)) != EOF)
    {
        if (strstr(SCOL, buf))
            continue;
        if (strstr(PLUS, buf))
            append(head, buf, plus);
        else if (strstr(LPAR, buf))
            append(head, buf, lpar);
        else if (strstr(RPAR, buf))
            append(head, buf, rpar);
        else if (strstr(PLUS, buf))
            append(head, buf, plus);
    };

    for (; head != NULL; head = head->next)
        printf(head->value);
}
