MAKEFLAGS += --silent

src := $(shell find src -name '*.c')
out := cattleship

default:
	$(CC) $(src) -lncurses -o $(out)

run: default
	./$(out)

format:
	clang-format -i $(src)

clean:
	rm -f $(out)