#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

typedef enum {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} ProcessState;

typedef struct {
    int pid;
    int arrival;
    int priority;
    int original_priority;
    ProcessState state;
    int *bursts;
    size_t burst_count;
    size_t current_burst;
    int remaining;
    int io_complete;
    size_t ready_order;
} Process;

#endif
