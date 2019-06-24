# Compile the compiler.
PC := fpc
PFLAGS := -TLINUX
PSRC := main.pas
PDIR := pascal_src
OBJS := main.o utils.o ops.o parser.o lexer.o
BIN := compiler

.PHONY: all pascal clean test

all: $(OBJS)
	$(CC) -o $(BIN) $^

pascal: $(PDIR)/$(PSRC)
	$(PC) $(PFLAGS) -o$(BIN) $^
	mv $(PDIR)/$(BIN) .

%.o: %.c
	$(CC) -o $@ -c $<

test:
	./$(BIN)

clean:
	rm -f *.o $(PDIR)/*.o $(BIN)
