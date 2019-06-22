/* parser.c: a top-down recursive descent parser. */
#include <stdio.h>
#include "ops.h"
#include "parser.h"
#include "utils.h"

extern char *progname; /* must be defined externally */

void expression(void)
{
    char c;

    term();
    while (TRUE) {
        if ((c = get_valid(VMOD_NL, progname)) != EOF) { /* allow '\n' */
            printf("MOVE D0, -(SP)\n"); /* -(SP) pushes onto stack */
            if (c == ops_sym[OP_ADD]) ops_fn[OP_ADD]();
            else if (c == ops_sym[OP_SUB]) ops_fn[OP_SUB]();
            else expected(progname, "OP_ADD or OP_SUB", c);
        } else /* EOF */
            break;
    }
}

void term(void)
{
    char c;

    if ((c = get_valid(VMOD_NNL, progname)) == EOF) /* don't allow '\n' */
        fail(progname, "unexpected end of input");
    printf("MOVE #%c, D0\n", c);
}
