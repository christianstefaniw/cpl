#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"

#define PRNT "print"

void visit_func_call(node *n, node *program)
{
    node *curr_node;
    if (strcmp(n->value->value, PRNT) == 0)
    {
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
            case ident:;
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
}

node *find_var(node *n, char *var)
{
    node *curr_node;

    for (int i = 0; i < n->children->len; i++)
    {
        curr_node = n->children->nodes[i];
        if (strcmp(curr_node->value->value, var) == 0)
            return curr_node->children->nodes[curr_node->children->len - 1];
        find_var(curr_node->children->nodes[i], var);
    }
}

// preorder traversal
node *traverse(node *n, node *program)
{
    // if (n->value != NULL)
    //    printf("%s\n", n->value->value);
    node *curr_node;

    if (n->children == NULL)
        return n;

    for (int i = 0; i < n->children->len; i++)
    {
        curr_node = n->children->nodes[i];
        if (curr_node->value->type == fn_call)
            visit_func_call(curr_node, program);
        else if (curr_node->value->type == scol)
            continue;

        traverse(curr_node, program);
    }
}

void eval(node *program)
{
    traverse(program, program);
    free(program);
}