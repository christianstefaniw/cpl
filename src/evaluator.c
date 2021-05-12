#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(node *nd)
{
    switch (nd->op->type)
    {
    case add:
        printf("%i\n", atoi(nd->left->value) + atoi(nd->right->value));
        free(nd);
    case mul:
        printf("%i\n", atoi(nd->left->value) * atoi(nd->right->value));
        free(nd);
    }
}