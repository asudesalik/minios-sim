#include "policies.h"

static size_t pick_fcfs(const Process *processes, size_t count)
{
    size_t selected = count;

    for (size_t i = 0; i < count; i++) {
        if (processes[i].state != READY) {
            continue;
        }

        if (selected == count ||
            processes[i].ready_order < processes[selected].ready_order ||
            (processes[i].ready_order == processes[selected].ready_order &&
             processes[i].pid < processes[selected].pid)) {
            selected = i;
        }
    }

    return selected;
}

const SchedulerPolicy FCFS_POLICY = {
    .name = "fcfs",
    .pick_next = pick_fcfs
};