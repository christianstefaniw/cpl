#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "evaluator.h"
#include "built_in_fn.h"

static scope *_scope;

void visit_func_call(node *n)
{
    if (strcmp(n->value->value, PRNT) == 0)
        print_fn(n);
    else
        run_user_defined_fn(n);
}

void run_user_defined_fn(node *n)
{
    node *fn = find_fn_dec(n->value->value);

    _scope->curr_fn = fn;

    traverse(fn);

    _scope->curr_fn = NULL;
}

node *find_fn_dec(char *ident)
{
    node *curr_node;

    for (int i = 0; i < _scope->program->children->len; i++)
    {
        curr_node = _scope->program->children->nodes[i];
        if (strcmp(curr_node->value->value, ident) == 0 && curr_node->value->type == fn_dec)
            return curr_node;
    }

    return NULL;
}

node *find_var(char *ident)
{
    node *curr_node;

    for (int i = 0; i < _scope->program->children->len; i++)
    {
        curr_node = _scope->program->children->nodes[i];
        if (strcmp(curr_node->value->value, ident) == 0 && curr_node->value->type == assign)
            return curr_node->children->nodes[curr_node->children->len - 1];
    }

    if (_scope->curr_fn == NULL)
        return NULL;

    for (int i = 0; i < _scope->curr_fn->children->len; i++)
    {
        curr_node = _scope->curr_fn->children->nodes[i];
        if (strcmp(curr_node->value->value, ident) == 0 && curr_node->value->type == assign)
            return curr_node->children->nodes[curr_node->children->len - 1];
    }

    return NULL;
}

node *traverse(node *n)
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
            visit_func_call(curr_node);
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
    _scope = malloc(sizeof _scope);
    _scope->program = program;

    node program_cpy = *program;
    traverse(&program_cpy);
    free(_scope);
    free(program);
}