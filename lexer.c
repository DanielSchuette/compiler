/* lexer.c: take a line from `stdin' and return a stream of tokens. */
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "ops.h"

extern char *progname;

/* lex_line: take a line from a stream and lex it. */
tokens *lex_line(FILE *stream)
{
    int i;
    char op;
    char *line;
    tokens *t;
    size_t n;

    line = NULL;
    n = 0;
#if _POSIX_C_SOURCE >= 200809L
    getline(&line, &n, stream); /* `*line' must be freed */
#else
    fprintf(stderr, "%s: error: need glibc >= 200809\n", progname);
    exit(1);
#endif
    n = strlen(line);

    t = (tokens *)malloc(sizeof(tokens));
    t->stream = (token_t **)malloc(MAX_TOKEN*sizeof(token_t *));
    t->len = 0;

    /* chars can be (1) invalid, (2) an op, (3) an int literal */
    for (i = 0; i < n; i++) {
        /* invalid chars */
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            continue;

        /* lex ops and integer literals */
        token_t *tok = (token_t *)malloc(sizeof(token_t));
        if ((op = is_op(line[i])) != ' ') {
            char *op_c;

            op_c = (char *)malloc(sizeof(char));
            *op_c = op;
            tok->op = op_c;
            tok->lit = NULL;
        } else if (isdigit(line[i])) {
            char *lit_c;
            int *lit_i;
            int k = 0;
            int len = strlen(&line[i])+1;

            lit_i = (int *)malloc(sizeof(int));
            lit_c = (char *)malloc(len*sizeof(char));
            while (isdigit(line[i]))
                lit_c[k++] = line[i++];

            i--;
            lit_c[k] = '\0';
            *lit_i = atoi(lit_c);
            tok->op = NULL;
            tok->lit = lit_i;
            free(lit_c);
        }
        t->stream[t->len++] = tok;
    }

    free(line);
    return t;
}

/* free_tokens: free a token stream. */
void free_tokens(tokens *t)
{
    size_t i;

    for (i = 0; i < t->len; i++) {
        free(t->stream[i]->op);
        free(t->stream[i]->lit);
        free(t->stream[i]);
    }
    free(t);
}

/* print_tokens: print a token stream to `stdout'. */
void print_tokens(tokens *t)
{
    int i;

    fprintf(stderr, "length: %lu\n", t->len);
    for (i = 0; i < t->len; i++) {
        if (t->stream[i]->op)
            fprintf(stderr, "op: %c\n", *(t->stream[i]->op));
        else
            fprintf(stderr, "lit: %d\n", *(t->stream[i]->lit));
    }
}

/* advance: advance a token stream by one if there are still tokens on it. */
void advance(tokens **t)
{
    ((*t)->len)--; /* decrement stream length */
    if ((*t)->len > 0)
        (*t)->stream++; /* advance token stream */
}
