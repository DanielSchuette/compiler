/* utils.c: Compiler utility functions. */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void expected(const char *prog, const char *msg, char c)
{
    fprintf(stderr, "%s: error: Expected %s, got %c.", prog, msg, c);
    exit(1);
}

/* skip: if the current character is unwanted, move on. */
char skip(char c)
{
    if (c == '\n' || c == '\t' || c == ' ')
        return fgetc(stdin);
    else
        return c;
}
