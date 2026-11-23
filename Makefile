CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread

.PHONY: all clean

all: minios

minios: src/main.c src/sched/input.c src/sched/policies.c src/sched/input.h src/sched/process.h src/sched/policies.h src/sched/scheduler.h src/sched/scheduler.c
	$(CC) $(CFLAGS) src/main.c src/sched/input.c src/sched/policies.c src/sched/scheduler.c -o minios 
clean:
	rm -f minios
