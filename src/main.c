#include <stdio.h>
#include "sched/process.h"

int main(void)
{
    int bursts[] = {5, 3, 2};
    Process p1 = {
        .pid = 1,
        .arrival = 0,
        .priority = 3,
        .original_priority = 3,
        .state = NEW,
        .bursts = bursts,
        .burst_count = sizeof(bursts) / sizeof(bursts[0]),
        .current_burst = 0,
        .remaining = bursts[0]
    };

    printf("MiniOS-Sim\n");
    printf("P%d: arrival=%d priority=%d\n",
           p1.pid, p1.arrival, p1.priority);
    for (size_t i = 0; i < p1.burst_count; i++) {
        printf("%s: %d\n", i % 2 == 0 ? "CPU" : "I/O", p1.bursts[i]);
    }
    return 0;
}
