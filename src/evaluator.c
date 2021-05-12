#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(token *tk)
{
    if (tk->type == call_exp && strcmp(tk->value, PRNT) == 0)
    {
        switch (tk->type)
        {
        default:
            printf("type not supported yet :(\n");
        }
    }
}