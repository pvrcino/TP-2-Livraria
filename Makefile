CC=clang-7
CFLAGS=-I. -Wall -g

SRC = src/Menu.c src/tAutor.c src/tLivro.c main.c

tp2: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o tp2
  