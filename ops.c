/* ops.c: operations recognized by the parser. */
#include <stdio.h>
#include "ops.h"
#include "parser.h"

char ops_sym[2] = {
    '+', '-'    /* valid in expressions */
};

op_fn ops_fn[2] = {
    add, sub    /* valid in expressions */
};

void add(void)
{
    term();
    printf("ADD (SP)+, D0\n"); /* (SP)+ pops from stack */
    return;
}

void sub(void)
{
    term();
    printf("SUB (SP)+, D0\n");
    printf("NEG D0\n");
    return;
}
