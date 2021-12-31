#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "built_in_fn.h"
#include "evaluator.h"

void print_fn(node *n, node *program)
{
    node *curr_node;

    for (int i = 0; i < n->children->len; i++)
    {
        curr_node = n->children->nodes[i];
        switch (curr_node->value->type)
        {
        case number:
            printf("%i\n", atoi(traverse(curr_node, program)->value->value));
            break;
        case string:
            printf("%s\n", traverse(curr_node, program)->value->value);
            break;
        case ident:
            node *var_node = find_var(program, curr_node->value->value);
            if (var_node->value->type == string)
                printf("%s\n", var_node->value->value);
            else if (var_node->value->type == number)
                printf("%i\n", atoi(var_node->value->value));
            else
                printf("identifier not found!\n");

            break;
        default:
            printf("ERROR!!!\n");
        }
    }
}