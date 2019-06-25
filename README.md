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
