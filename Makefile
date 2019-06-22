# Compile the compiler.
PC := fpc
PFLAGS := -TLINUX
PSRC := main.pas
OBJS := main.o utils.o ops.o parser.o
BIN := compiler

.PHONY: all clean test

all: $(OBJS)
	$(CC) -o $(BIN) $^

pascal: $(PSRC)
	$(PC) $(PFLAGS) -o$(BIN) $^

%.o: %.c
	$(CC) -o $@ -c $<

test:
	./$(BIN)

clean:
	rm -f *.o $(BIN)
