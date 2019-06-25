/* ops.c: operations recognized by the parser. */
#include <stdio.h>
#include "ops.h"

char ops_sym[NUM_OPS] = {
    '+', '-',       /* valid in expressions */
    '*', '/',       /* valid in terms */
};

op_fn ops_fn[NUM_OPS] = {
    _add, _sub,     /* valid in expressions */
    _mult, _div,    /* valid in terms */
};

void _mult(tokens **t, pnode_t *n)
{
    advance(t);
    factor(t, n);
    printf("\tMULS (SP)+, D0\n");
}

void _div(tokens **t, pnode_t *n)
{
    advance(t);
    factor(t, n);
    printf("\tMOVE (SP)+, D1\n");
    printf("\tDIVS D1, D0\n");
}

void _add(tokens **t, pnode_t *n)
{
    advance(t);
    term(t, n);
    printf("\tADD (SP)+, D0\n"); /* (SP)+ pops from stack */
}

void _sub(tokens **t, pnode_t *n)
{
    advance(t);
    term(t, n);
    printf("\tSUB (SP)+, D0\n");
    printf("\tNEG D0\n");
}

/* is_op: if `c' is a valid token, it's returned, otherwise ' ' is returned. */
char is_op(char c)
{
    int i;

    for (i = 0; i < NUM_OPS; i++)
        if (c == ops_sym[i])
            return c;
    return ' ';
}
