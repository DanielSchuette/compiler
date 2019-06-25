/* main.c: parse an expression from stdin. */
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "utils.h"

const char *progname;

int main(int argc, char **argv)
{
    int i;
    int debug;
    tokens *tokens;

    debug = 0;
    progname = argv[0];

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--help") ||
            !strcmp(argv[i], "-h"))
            usage(progname);
        if (!strcmp(argv[i], "--file") ||
            !strcmp(argv[i], "-f"))
            fprintf(stderr, "%s: warning: -f is not implemented\n", progname);
        if (!strcmp(argv[i], "--debug") ||
            !strcmp(argv[i], "-d"))
            debug = 1;
    }

    tokens = lex_line(stdin);
    if (debug)
        print_tokens(tokens);
    expression(&tokens);
    free_tokens(tokens);

    return 0;
}
