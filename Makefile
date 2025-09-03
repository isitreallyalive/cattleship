MAKEFLAGS += --silent

src := main.c
out := cattleship

default:
	$(CC) $(src) -o $(out)

run: default
	./$(out)

clean:
	rm -f $(out)