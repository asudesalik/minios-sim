#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct {
    const char *name;
    size_t (*pick_next)(const Process *processes, size_t count);
} SchedulerPolicy;

int run_scheduler(Process *processes, size_t count,
                  const SchedulerPolicy *policy);

#endif