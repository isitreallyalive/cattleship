MAKEFLAGS += --silent
CFLAGS += -I./src/struct -I./src/util

src := $(shell find src -name '*.c')
out := cattleship

default:
	$(CC) $(CFLAGS) $(src) -lncurses -o $(out)

run: default
	./$(out)

format:
	clang-format -i $(src)

clean:
	rm -f $(out)