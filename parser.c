/* parser.c: a top-down recursive descent parser. */
#include <stdio.h>
#include "ops.h"
#include "parser.h"
#include "utils.h"

extern char *progname;

/* expression: parse an expression. */
void expression(tokens **tokens)
{
    char c;

    term(tokens);
    while (TRUE) {
        if ((c = get_valid(VMOD_NL, progname)) != EOF) { /* allow '\n' */
            if (c != ops_sym[OP_ADD] && c != ops_sym[OP_SUB]) {
                ungetc(c, stdin);
                break;
            };

            printf("\tMOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */
            if (c == ops_sym[OP_ADD]) ops_fn[OP_ADD](tokens);
            else if (c == ops_sym[OP_SUB]) ops_fn[OP_SUB](tokens);
        } else /* EOF */
            break;
    }
}

/* term: parse a term. */
void term(tokens **tokens)
{
    char c;

    factor(tokens);
    while (TRUE){
        if ((c = get_valid(VMOD_NL, progname)) != EOF) {
            if (c != ops_sym[OP_MULT] && c != ops_sym[OP_DIV]) {
                ungetc(c, stdin);
                break;
            };

            printf("\tMOVE D0, -(SP)\n");
            if (c == ops_sym[OP_MULT]) ops_fn[OP_MULT](tokens);
            else if (c == ops_sym[OP_DIV]) ops_fn[OP_DIV](tokens);
        } else
            break;
    }
}

/* factor: parse a factor. */
void factor(tokens **tokens)
{
    char c;

    if ((c = get_valid(VMOD_NNL, progname)) == EOF) /* don't allow '\n' */
        fail(progname, "unexpected end of input");
    printf("\tMOVE #%c, D0\n", c);
}
