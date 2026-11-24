#include <stdio.h>
#include "scheduler.h"

static void admit_ready(Process *processes, size_t count,
                        int time, size_t *next_order)
{
    while (1) {
        size_t selected = count;

        for (size_t i = 0; i < count; i++) {
            int arrived = processes[i].state == NEW &&
                          processes[i].arrival == time;

            int io_finished = processes[i].state == WAITING &&
                              processes[i].io_complete == time;

            if (!arrived && !io_finished) {
                continue;
            }

            if (selected == count ||
                processes[i].pid < processes[selected].pid) {
                selected = i;
            }
        }

        if (selected == count) {
            break;
        }

        processes[selected].state = READY;
        processes[selected].ready_order = (*next_order)++;
    }
}
static int finish_cpu_burst(Process *process, int time)
{
    if (process->current_burst + 1 == process->burst_count) {
        process->state = TERMINATED;
        process->completion = time;
        return 1;
    }

    process->state = WAITING;
    process->io_complete =
        time + process->bursts[process->current_burst + 1];

    process->current_burst += 2;
    process->remaining = process->bursts[process->current_burst];

    return 0;
}
int run_scheduler(Process *processes, size_t count,
                  const SchedulerPolicy *policy)
{
    int time = 0;
    size_t completed = 0;
    size_t running = count;
    size_t next_order = 0;

    while (completed < count) {
        admit_ready(processes, count, time, &next_order);

        if (running != count && processes[running].remaining == 0) {
            completed += finish_cpu_burst(&processes[running], time);
            running = count;
        }

        if (completed == count) {
            break;
        }

        if (running == count) {
            running = policy->pick_next(processes, count);

            if (running != count) {
    processes[running].state = RUNNING;

    if (!processes[running].has_started) {
        processes[running].first_dispatch = time;
        processes[running].has_started = 1;
    }
}
        }

        if (running == count) {
            printf("t=%d IDLE\n", time);
        } else {
            printf("t=%d P%d\n", time, processes[running].pid);
            processes[running].remaining--;
        }
        for (size_t i = 0; i < count; i++) {
    if (processes[i].state == READY) {
        processes[i].waiting++;
    }
}

        time++;
    }
        printf("\nPID Arrival Completion Turnaround Waiting Response\n");

    for (size_t i = 0; i < count; i++) {
        int turnaround = processes[i].completion - processes[i].arrival;
        int response = processes[i].first_dispatch - processes[i].arrival;

        printf("P%d %d %d %d %d %d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].completion,
               turnaround,
               processes[i].waiting,
               response);
    }

    return 0;
}