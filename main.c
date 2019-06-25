/* main.c: parse an expression from stdin. */
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "utils.h"

const char *progname;

int main(int argc, char **argv)
{
    int i, debug;
    tokens *tokens;
    pnode_t *tree;

    debug = 0;
    progname = argv[0];

    /* collect options and flags */
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
            usage(progname);
        if (!strcmp(argv[i], "--file") || !strcmp(argv[i], "-f"))
            /* TODO: implement */
            fprintf(stderr, "%s: warning: -f is not implemented\n", progname);
        if (!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d"))
            debug = 1;
    }

    /* lex and parse an input line */
    tokens = lex_line(stdin);
    if (debug)
        print_tokens(tokens);
    tree = parse(&tokens);

    /* free resources */
    free_tokens(tokens);
    free_nodes(tree);

    return 0;
}
