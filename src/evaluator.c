#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

void eval(node *program)
{
    printf("%i\n", program->children->len);
    free(program);
}