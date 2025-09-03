MAKEFLAGS += --silent

src := $(shell find src -name '*.c')
out := cattleship

default:
	$(CC) $(src) -lncurses -o $(out)

run: default
	./$(out)

clean:
	rm -f $(out)