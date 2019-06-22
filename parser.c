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
        if ((c = fgetc(stdin)) != EOF && (c = skip(c)) != EOF) {
            printf("MOVE D0, D1\n"); /* store register */
            if (c == ops_sym[OP_ADD]) ops_fn[OP_ADD]();
            else if (c ==ops_sym[OP_SUB]) ops_fn[OP_SUB]();
            else expected(progname, "OP_ADD or OP_SUB", c);
        } else /* EOF */
            break;
    }
}

void term(void)
{
    char c;
    c = fgetc(stdin);
    printf("MOVE #%c, D0\n", c);
}
