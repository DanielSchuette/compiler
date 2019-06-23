# Grammar
The following grammar is recognized by the parser:

```
{ <expression> ::= <term> [ <addop> <term> ]* }
{ <term> ::= <factor> [ <mulop> <factor> ]* }
{ <factor> ::= <digit> }
```
