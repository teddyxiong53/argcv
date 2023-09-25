CC = gcc
CFLAGS = -Wall -Wextra -g

all: test

test: test.c argcv.c
	$(CC) $(CFLAGS)  -o test test.c argcv.c

clean:
	rm -f test
