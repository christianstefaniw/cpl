#include <stdlib.h>
#include "../lexer/lexer.h"

#define MULTIPLE_SEP ','
#define END ';'

void parse_expression()
{

}

void parse(token *head)
{
    while (head->next != NULL)
    {
        printf("type: %i, value:%s\n", head->type, head->value);
        head = head->next;
    }
    
}