#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"
#include "built_in_fn.h"

#define PRNT "print"

void visit_func_call(node *n, node *program)
{
    if (strcmp(n->value->value, PRNT) == 0)
        print_fn(n, program);
    else
        run_user_defined_fn(n, program);
}

void run_user_defined_fn(node *n, node *program)
{
    node *fn = find_fn_dec(program, n->value->value);

    traverse(fn, program);
}

node *find_fn_dec(node *program, char *ident)
{
    node *curr_node;

    for (int i = 0; i < program->children->len; i++)
    {
        curr_node = program->children->nodes[i];
        if (strcmp(curr_node->value->value, ident) == 0 && curr_node->value->type == fn_dec)
            return curr_node;
    }

    return NULL;
}

node *find_var(node *program, char *ident)
{
    node *curr_node;

    for (int i = 0; i < program->children->len; i++)
    {
        curr_node = program->children->nodes[i];
        if (strcmp(curr_node->value->value, ident) == 0 && curr_node->value->type == assign)
            return curr_node->children->nodes[curr_node->children->len - 1];
    }

    return NULL;
}

node *traverse(node *n, node *program)
{
    node *curr_node;

    if (n->children == NULL)
        return n;

    for (int i = 0; i < n->children->len; i++)
    {
        curr_node = n->children->nodes[i];
        if (curr_node->value->type == fn_dec)
            continue;
        else if (curr_node->value->type == fn_call)
            visit_func_call(curr_node, program);
        else if (curr_node->value->type == scol)
            continue;
    }

    return NULL;
}

void move_to_end_of_fn_dec(node *curr_node)
{
    for (int i = 0; i < curr_node->children->len; i++)
    {
        if (curr_node->children->nodes[i]->value->type == rbrace)
        {
            *curr_node = *curr_node->children->nodes[i];
            return;
        }
    }
}

void eval(node *program)
{
    node program_cpy = *program;
    traverse(&program_cpy, program);
    free(program);
}