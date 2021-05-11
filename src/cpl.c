#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "helpers.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

#define CPL_EXTENSION "cpl"

int is_cpl(char *file_name)
{
    char buff[strlen(file_name)];
    char *found, *buff_ptr;
    unsigned int iters;
    size_t num_dots;

    strcpy(buff, file_name);
    buff_ptr = buff;

    num_dots = count_characters(file_name, '.');
    while ((found = strsep(&buff_ptr, ".")) != NULL)
    {
        if (iters != num_dots)
        {
            iters++;
            continue;
        }
        if (strcmp(found, CPL_EXTENSION) == 0)
            return 1;
        return 0;
    }
}

int main(int argc, char *argv[])
{
    FILE *cpl_file;
    char *cpl_file_name;

    cpl_file_name = argv[argc - 1];
    
    if (is_cpl(cpl_file_name))
    {
        if ((cpl_file = fopen(cpl_file_name, "r")) == NULL)
        {
            fprintf(stderr, "%s\n", strerror(errno));
            return 1;
        }
        parse(cpl_file);
        return 0;
    }

    fprintf(stderr, "file does not have the .cpl extension!\n");
    return 1;
}