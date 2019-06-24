#ifndef _LEXER_H_
#define _LEXER_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN 1024 /* never reallocated, > than this is unreasonable */

typedef struct { /* either one must be a NULL ptr */
    int *lit;
    char *op;
} token_t;

typedef struct tokens {
    token_t **stream;
    size_t len;
} tokens;

tokens *lex_line(FILE *);
void free_tokens(tokens *);
void print_tokens(tokens *);

#endif /* _LEXER_H_ */
