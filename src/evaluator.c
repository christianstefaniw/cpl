#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(node *root)
{
    if (root->value->type == fn_call)
    {
        if (strcmp(root->value->value, PRNT) == 0)
        {
            for (int i = 0; i < root->children->len; i++)
                for (int k = 0; k < root->children->nodes[i]->children->len; k++)
                    printf("%s\n", root->children->nodes[i]->children->nodes[k]->value->value);
        }
    }

    free(root);
}