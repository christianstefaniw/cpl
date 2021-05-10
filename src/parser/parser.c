#include <stdlib.h>
#include "../lexer/lexer.h"

#define MULTIPLE_SEP ','
#define END ';'

void parse_expression()
{

}

void parser(token *head)
{
    while (head->next != NULL)
    {
        
        head = head->next;
    }
    
}