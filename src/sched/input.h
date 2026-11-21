#ifndef SCHED_INPUT_H
#define SCHED_INPUT_H

#include "process.h"

int read_process_file(const char *path, Process **processes, size_t *count);
void free_processes(Process *processes, size_t count);

#endif
