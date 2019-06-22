/* utils.c: Compiler utility functions. */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

const static char* help_msg =
"Counts to 25 minutes in 1 second intervals, asking you to do work. Then,\n"
"a break of 5 minutes is recommended. These intervals might be changed.\n"
"Author: Daniel Schuette <d.schuette@online.de>\n"
"Date: 2019/06/23\n"
"Sources: https://github.com/DanielSchuette/compiler\n"
"License: GPLv3 (https://www.gnu.org/licenses/gpl-3.0.en.html)\n"
"\n"
"USAGE:\n"
"\t%s [FLAGS] [OPTIONS]\n"
"\n"
"FLAGS:\n"
"\t-h, --help\t\tDisplay this help message\n"
"\n"
"OPTIONS:\n"
"\t-f, --file <FILE>\tSupply expression via <FILE> instead of `stdin'\n"
"\t\t\t(not yet supported).\n";

void fail(const char *prog, const char *msg)
{
    fprintf(stderr, "%s: error: %s.\n", prog, msg);
    exit(1);
}

void expected(const char *prog, const char *msg, char c)
{
    fprintf(stderr, "%s: error: expected %s, got %c.\n", prog, msg, c);
    exit(1);
}

/* get_valid: get chars from `stdin', it's returned if it's valid. */
char get_valid(char mode, const char *prog)
{
    char c;

    while ((c = fgetc(stdin))) {
        switch (mode) {
            case VMOD_NNL:
                if (c == '\n')
                    fail(prog, "Unexpected end of input");
                /* fall through */
            case VMOD_NL:
                if (c == '\n' || c == '\t' || c == ' ')
                    continue;
                else
                    return c;
        }
    }
    return EOF; /* never reached */
}

void usage(const char *prog)
{
    fprintf(stderr, help_msg, prog);
    exit(0);
}
