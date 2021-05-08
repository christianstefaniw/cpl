#include <string.h>

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