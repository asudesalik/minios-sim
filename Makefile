CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread

.PHONY: all clean

all: minios

minios: src/main.c src/sched/input.c src/sched/input.h src/sched/process.h
	$(CC) $(CFLAGS) src/main.c src/sched/input.c -o minios

clean:
	rm -f minios
