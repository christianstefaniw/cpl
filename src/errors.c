#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "errors.h"

void check_semicolon_error(int tk_type)
{
    if (tk_type == newline)
    {
        fprintf(stderr, "error: missing semicolon\n");
        exit(1);
    }
}