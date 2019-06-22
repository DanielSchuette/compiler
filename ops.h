#ifndef _OPS_H_
#define _OPS_H_

/* indices into ops arrays */
#define OP_ADD 0
#define OP_SUB 1

typedef void (*op_fn)(void);

void add(void);
void sub(void);

/* operation symbols and associated actions */
op_fn ops_fn[2];
char ops_sym[2];

#endif /* _OPS_H_ */
