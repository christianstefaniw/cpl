#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(node *expr)
{
    if (expr->type == call_exp && strcmp(expr->value, PRNT) == 0)
    {
        switch (expr->param->type)
        {
        case num_lit:
            printf("%i\n", atoi(expr->param->value));
            break;
        case str_lit:
            printf("%s\n", expr->param->value);
            break;
        default:
            printf("type not supported yet :(\n");
        }
    }
}