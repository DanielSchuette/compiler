/* parser.c: a top-down recursive descent parser. */
#include <stdio.h>
#include "ops.h"
#include "parser.h"
#include "utils.h"

extern char *progname;

/*
 * TODO:
 *      - add expressions, terms, and factors to the parse tree.
 *      - visualize the parse tree (dot?)
 *      - clean up resources afterwards
 */


/* parse: start parsing a token stream. */
pnode_t *parse(tokens **t)
{
    pnode_t *n;

    n = (pnode_t *)malloc(sizeof(pnode_t));
    expression(t, n);
    return n;
}

/* expression: parse an expression. */
void expression(tokens **tokens, pnode_t *node)
{
    char *op;

    term(tokens, node);
    while (TRUE) {
        if (len(tokens) > 0) op = get_op(tokens);
        else op = NULL;
        if (op) {
            if (*op != ops_sym[OP_ADD] && *op != ops_sym[OP_SUB])
                break;

            printf("\tMOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */

            if (*op == ops_sym[OP_ADD]) ops_fn[OP_ADD](tokens, node);
            else if (*op == ops_sym[OP_SUB]) ops_fn[OP_SUB](tokens, node);
        } else if (get_lit(tokens) && len(tokens) > 0)
            expected_op(progname, "`+' or `-'", *get_lit(tokens));
        else
            break;
    }
}

/* term: parse a term. */
void term(tokens **tokens, pnode_t *node)
{
    char *op;

    factor(tokens, node);
    while (TRUE) {
        if (len(tokens) > 0) op = get_op(tokens);
        else op = NULL;
        if (op) {
            if (*op != ops_sym[OP_MULT] && *op != ops_sym[OP_DIV])
                break;

            printf("\tMOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */
            if (*op == ops_sym[OP_MULT]) ops_fn[OP_MULT](tokens, node);
            else if (*op == ops_sym[OP_DIV]) ops_fn[OP_DIV](tokens, node);
        } else if (get_lit(tokens) && len(tokens) > 0)
            expected_op(progname, "`*' or `/'", *get_lit(tokens));
        else
            break;
    }
}

/* factor: parse a factor. */
void factor(tokens **tokens, pnode_t *node)
{
    int *lit;

    if (len(tokens) < 1)
        fail(progname, "unexpected end of input");
    lit = get_lit(tokens);
    if (!lit)
        expected_lit(progname, "an integer literal", *get_op(tokens));
    else
        printf("\tMOVE #%d, D0\n", *lit);
    advance(tokens);
}

/* free_nodes: free a parse tree bottom-up. */
void free_nodes(pnode_t *n)
{
    free(n);
}
