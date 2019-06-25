/* utils.c: Compiler utility functions. */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

const static char* help_msg =
"Compile simple math expressions to 68000 assembly language."
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
"\t-d, --debug\t\tEnable debug mode\n"
"\n"
"OPTIONS:\n"
"\t-f, --file <FILE>\tRead expressions from <FILE> instead of `stdin'\n";

/* fail: print formatted `msg' and exit. */
void fail(const char *prog, const char *msg)
{
    fprintf(stderr, "%s: error: %s.\n", prog, msg);
    exit(1);
}

/* expected: print formatted `msg' and exit. */
void expected_lit(const char *prog, const char *msg, char c)
{
    fprintf(stderr, "%s: error: expected %s, got %c.\n", prog, msg, c);
    exit(1);
}

void expected_op(const char *prog, const char *msg, int lit)
{
    fprintf(stderr, "%s: error: expected %s, got %d.\n", prog, msg, lit);
    exit(1);
}

void expected_pos(const char *prog, const char *msg, const char *line, int pos)
{
    int i;

    fprintf(stderr, "%s: error: invalid character, got %c.\n\t%s\t",
            prog, line[pos], line);
    for (i = 0; i < pos; i++)
        fputc('-', stderr);
    fprintf(stderr, "^\n");
    exit(1);
}

/*
 * get_valid: get chars from `stdin', the first valid one is returned.
 * This function is currently unused.
 */
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

/* usage: print help string and exit. */
void usage(const char *prog)
{
    fprintf(stderr, help_msg, prog);
    exit(0);
}
