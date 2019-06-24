#ifndef _OPS_H_
#define _OPS_H_

#include "lexer.h"

/* indices into ops arrays */
#define OP_ADD  0
#define OP_SUB  1
#define OP_MULT 2
#define OP_DIV  3
#define NUM_OPS 4

typedef void (*op_fn)(tokens **);

void _add(tokens **);
void _sub(tokens **);
void _mult(tokens **);
void _div(tokens **);

/* operation symbols and associated actions */
op_fn ops_fn[NUM_OPS];
char ops_sym[NUM_OPS];

char is_op(char);

#endif /* _OPS_H_ */
