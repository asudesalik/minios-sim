CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread

.PHONY: all clean

all: minios

minios: src/main.c
	$(CC) $(CFLAGS) src/main.c -o minios

clean:
	rm -f minios
