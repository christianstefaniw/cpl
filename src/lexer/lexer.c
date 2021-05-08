#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define OPERATION "operation"
#define OPERATORS "+-*/"

void lex(FILE *cpl_file)
{
    unsigned int src_char;
    token *head = NULL;
    token *tail = NULL;

    while ((src_char = fgetc(cpl_file)) != EOF)
    {
        if (strchr(OPERATORS, src_char))
        {
            // alloca is ok for now
            token *temp = alloca(sizeof(token));

            temp->value = src_char;
            temp->next = NULL;

            if (tail == NULL)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = temp;
            }
        }
    }
    for (; head != NULL; head = head->next)
        printf("%c", head->value);
}
