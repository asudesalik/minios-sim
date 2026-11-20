#include <stdio.h>
#include "sched/process.h"

int main(void)
{
    Process p1 = {
        .pid = 1,
        .arrival = 0,
        .priority = 3,
        .original_priority = 3,
        .state = NEW
    };

    printf("MiniOS-Sim\n");
    printf("P%d: arrival=%d priority=%d\n",
           p1.pid, p1.arrival, p1.priority);
    return 0;
}
