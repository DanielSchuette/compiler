/* parser.c: a top-down recursive descent parser. */
#include <stdio.h>
#include "ops.h"
#include "parser.h"
#include "utils.h"

extern char *progname;

/* parse: start parsing a token stream. */
void parse(tokens **t)
{
    expression(t);
}

/* expression: parse an expression. */
void expression(tokens **tokens)
{
    char *op;

    term(tokens);
    while (TRUE) {
        if (len(tokens) > 0) op = get_op(tokens);
        else op = NULL;
        if (op) {
            if (*op != ops_sym[OP_ADD] && *op != ops_sym[OP_SUB])
                break;

            printf("\tMOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */
            if (*op == ops_sym[OP_ADD]) ops_fn[OP_ADD](tokens);
            else if (*op == ops_sym[OP_SUB]) ops_fn[OP_SUB](tokens);
        } else if (get_lit(tokens) && len(tokens) > 0)
            fail(progname, "expected an integer literal");
        else
            break;
    }
}

/* term: parse a term. */
void term(tokens **tokens)
{
    char *op;

    factor(tokens);
    while (TRUE) {
        if (len(tokens) > 0) op = get_op(tokens);
        else op = NULL;
        if (op) {
            if (*op != ops_sym[OP_MULT] && *op != ops_sym[OP_DIV])
                break;

            printf("\tMOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */
            if (*op == ops_sym[OP_MULT]) ops_fn[OP_MULT](tokens);
            else if (*op == ops_sym[OP_DIV]) ops_fn[OP_DIV](tokens);
        } else if (get_lit(tokens) && len(tokens) > 0)
            fail(progname, "expected an integer literal");
        else
            break;
    }
}

/* factor: parse a factor. */
void factor(tokens **tokens)
{
    int *lit;

    if (len(tokens) < 1)
        fail(progname, "unexpected end of input");
    lit = get_lit(tokens);
    if (!lit)
        expected(progname, "an integer literal", *get_op(tokens));
    else
        printf("\tMOVE #%d, D0\n", *lit);
    advance(tokens);
}
