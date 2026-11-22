#include <stdio.h>
#include "sched/input.h"
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 5 ||
        strcmp(argv[1], "sched") != 0 ||
        strcmp(argv[2], "-a") != 0 ||
        strcmp(argv[3], "fcfs") != 0) {
        fprintf(stderr, "error: usage: ./minios sched -a fcfs FILE\n");
        return 1;
    }

    Process *processes = NULL;
    size_t count = 0;

    if (read_process_file(argv[4], &processes, &count) != 0) {
        return 1;
    }

    printf("Loaded processes: %zu\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("P%d arrival=%d priority=%d bursts:",
               processes[i].pid, processes[i].arrival, processes[i].priority);
        for (size_t j = 0; j < processes[i].burst_count; j++) {
            printf(" %d", processes[i].bursts[j]);
        }
        printf("\n");
    }

    free_processes(processes, count);
    return 0;
}
