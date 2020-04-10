# Compile the compiler.
PC := fpc
PFLAGS := -TLINUX
FLAGS := # -d -f
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

test_interactive:
	./$(BIN) $(FLAGS)

test_assembly:
	@rm -f add.* add
	@echo '1+2-7+9' | ./$(BIN) > add.s
	as add.s -o add.o
	ld add.o -o add
	@./add || echo "returned $$?"

clean:
	rm -f *.o $(PDIR)/*.o $(BIN) $(PDIR)/main
	rm -f add.* add
