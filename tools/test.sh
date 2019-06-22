#!/bin/sh
EXPRESSION='1+2/3*4/5+1+2/9/1*8'
PAS_TMP='tmp.pas'
C_TMP='tmp.c'

# test pascal and c versions
make pascal
echo "$EXPRESSION" | ./compiler > $PAS_TMP 2>&1
make clean
make
echo "$EXPRESSION" | ./compiler > $C_TMP 2>&1

# print diff
diff -s $PAS_TMP $C_TMP

# clean up
rm $PAS_TMP $C_TMP
