#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"



void init_growable_buff(growable_buf *buf_g, size_t cap)
{
    buf_g->buffer = malloc(cap * sizeof(char));
    buf_g->cap = cap;
    buf_g->len = 0;
}

void insert_growable_buff(growable_buf *buf_g, char elem)
{
    if (buf_g->len == buf_g->cap)
    {
        buf_g->cap *= 2;
        buf_g->buffer = realloc(buf_g->buffer, buf_g->cap * sizeof(char));
    }
    buf_g->buffer[buf_g->len++] = elem;
    buf_g->buffer[buf_g->len+1] = '\0';
}

void free_growable_buff(growable_buf *buf_g)
{
    free(buf_g->buffer);
    buf_g->buffer = NULL;
    buf_g->len = 0;
}

int count_characters(const char *str, char character)
{
    const char *p = str;
    int count = 0;

    do
    {
        if (*p == character)
            count++;
    } while (*(p++));

    return count;
}

int index_at(char *value, char find)
{
    char *ptr;
    int index;

    ptr = strchr(value, find);
    if (ptr)
        index = ptr - value;

    return index;
}