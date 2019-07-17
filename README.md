# Compiler

## Overview
`compiler` is a simple lexer, parser and compiler of math expressions. It's an example of the principles of parsing and compiler writing.

## Compile and Test
Compile from source by typing:
```bash
make # ignore any other targets in the make file!
make clean # clean up object files and the binary after compilation
make test # test the compilation success
```

`GRAMMAR.md` lists the productions for the supported expressions. Try compiling an expression by typing:
```bash
./compiler # requires a successful `make', use `--help' for additional information
# Type an expression and observe the output
```

## Examples
A successful compilation yields:

```bash
./compiler
1+9/2*12-1
#        MOVE #1, D0
#        MOVE D0, -(SP)
#        MOVE #9, D0
#        MOVE D0, -(SP)
#        MOVE #2, D0
#        MOVE (SP)+, D1
#        DIVS D1, D0
#        MOVE D0, -(SP)
#        MOVE #12, D0
#        MULS (SP)+, D0
#        ADD (SP)+, D0
#        MOVE D0, -(SP)
#        MOVE #1, D0
#        SUB (SP)+, D0
#        NEG D0
```

If the expression contains errors, a helpful error message is displayed:
```bash
./compiler
1+              u
#./compiler: error: invalid character, got u.
#        1+              u
#        ----------------^
```
## License
The code in this repository is licensed under the [GPLv3 license](./LICENSE.md).
