#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

/*
 * Grammar:
 * <expression> ::= <term> [ <addop> <term> ]*
 * <term> ::= <factor> [ <mulop> <factor> ]*
 * <factor> ::= <digit>
 */
void parse(tokens **);
void expression(tokens **);
void term(tokens **);
void factor(tokens **);

#endif /* _PARSER_H_ */
