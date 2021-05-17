#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void visit_func_call(node *n)
{
    if (strcmp(n->value->value, PRNT) == 0)
    {
        for (int i = 0; i < n->children->len; i++)
        {
            
            switch (n->children->nodes[i]->value->type)
            {
            case number:
                printf("%i\n", atoi(traverse(n->children->nodes[i])->value->value));
                break;
            case string:
                printf("%s\n", traverse(n->children->nodes[i])->value->value);
                break;
            default:
                printf("type not supported yet!");
            }
        }
    }
}

node *traverse(node *n)
{
    // if (n->value != NULL)
    //    printf("%s\n", n->value->value);

    if (n->children == NULL)
        return n;

    for (int i = 0; i < n->children->len; i++)
    {
        if (n->children->nodes[i]->value->type == fn_call)
            visit_func_call(n->children->nodes[i]);

        traverse(n->children->nodes[i]);
    }
}

void eval(node *program)
{
    traverse(program);
    free(program);
}