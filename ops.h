#ifndef _OPS_H_
#define _OPS_H_

#include "lexer.h"
#include "parser.h"

/* indices into ops arrays */
#define OP_ADD  0
#define OP_SUB  1
#define OP_MULT 2
#define OP_DIV  3
#define NUM_OPS 4

typedef void (*op_fn)(tokens **, pnode_t *);

void _add(tokens **, pnode_t *);
void _sub(tokens **, pnode_t *);
void _mult(tokens **, pnode_t *);
void _div(tokens **, pnode_t *);

/* operation symbols and associated actions */
op_fn ops_fn[NUM_OPS];
char ops_sym[NUM_OPS];

char is_op(char);

#endif /* _OPS_H_ */
