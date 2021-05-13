#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(expression_node *nd)
{
    switch (nd->op->type)
    {
    case add:
        printf("%i\n", atoi(nd->left->value) + atoi(nd->right->value));
        break;
    case mul:
        printf("%i\n", atoi(nd->left->value) * atoi(nd->right->value));
        break;
    case subt:
        printf("%i\n", atoi(nd->left->value) - atoi(nd->right->value));
        break;
    case divi:
        printf("%i\n", atoi(nd->left->value) / atoi(nd->right->value));
        break;
    }
    free(nd);
}