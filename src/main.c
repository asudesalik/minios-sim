#include <stdio.h>
#include "sched/input.h"

int main(void)
{
    Process *processes = NULL;
    size_t count = 0;

    if (read_process_file("tests/sched_io.txt", &processes, &count) != 0) {
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
