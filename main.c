/* main.c: parse an expression from stdin. */
#include "parser.h"

char *progname;

int main(int argc, char **argv)
{
    /* parse an expression from stdin */
    progname = argv[0];
    expression();

    return 0;
}
