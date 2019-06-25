#ifndef _UTILS_H_
#define _UTILS_H_

#define FALSE 0
#define TRUE !FALSE

#define VMOD_NNL    0   /* next char cannot be '\n' */
#define VMOD_NL     1   /* next char can be '\n', '\t' or ' ' */

void expected(const char *, const char *, char);
void expected_pos(const char *, const char *, const char *, int);
void fail(const char *, const char *);
char get_valid(char, const char *);
void usage(const char *);

#endif /* _UTILS_H_ */
