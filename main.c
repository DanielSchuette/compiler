/* main.c: parse an expression from stdin. */
#include "parser.h"
#include "utils.h"

const char *progname;

int main(int argc, char **argv)
{
    progname = argv[0];

    if (argc != 1) /* FIXME: check actual arguments */
        usage(progname);

    expression();

    return 0;
}
