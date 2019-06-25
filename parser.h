#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

typedef struct pnode_t {
    struct pnode_t *leftc;      /* left child (might be only child) */
    struct pnode_t *rightc;     /* right child (might be NULL) */
    token_t attr;               /* the token associated with this node */
} pnode_t;

/*
 * Grammar:
 * <expression> ::= <term> [ <addop> <term> ]*
 * <term> ::= <factor> [ <mulop> <factor> ]*
 * <factor> ::= <digit>
 */
pnode_t *parse(tokens **);
void expression(tokens **, pnode_t *);
void term(tokens **, pnode_t *);
void factor(tokens **, pnode_t *);

void free_nodes(pnode_t *);

#endif /* _PARSER_H_ */
