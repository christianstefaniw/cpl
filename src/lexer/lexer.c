#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define OPERATION "operation"
#define OPERATORS "+-*/"

// end of line
#define EOL "eol"
#define EOL_SYMBOL ";"

token *append(token *head, char src_char, char *type)
{
    token *cursor = head;
    token *new_tk = malloc(sizeof(token));

    new_tk->value = strdup(&src_char)[0];
    new_tk->type = type;
    new_tk->next = NULL;

    while (cursor->next != NULL)
        cursor = cursor->next;

    cursor->next = new_tk;

    return new_tk;
}

void lex(FILE *cpl_file)
{
    char src_char;
    token *head = malloc(sizeof(token));

    while ((src_char = fgetc(cpl_file)) != EOF)
    {
        if (strchr(OPERATORS, src_char))
            append(head, src_char, OPERATION);
        else if (strchr(EOL_SYMBOL, src_char))
            append(head, src_char, EOL);
    }

    for (; head != NULL; head = head->next)
        printf("%c", head->value);

    //
}
