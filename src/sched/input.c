#include <stdio.h>
#include "input.h"
#include "process.h"

int read_process_file(const char *path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        fprintf(stderr, "error: cannot open input file\n");
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        Process process = {0};

        if (sscanf(line, "P%d %d %d",
                   &process.pid,
                   &process.arrival,
                   &process.priority) != 3) {
            fprintf(stderr, "error: invalid process input\n");
            fclose(file);
            return 1;
        }

        if (process.pid < 0 || process.arrival < 0 || process.priority < 0) {
            fprintf(stderr, "error: negative process value\n");
            fclose(file);
            return 1;
        }

        process.original_priority = process.priority;
        process.state = NEW;

        printf("P%d arrival=%d priority=%d\n",
               process.pid, process.arrival, process.priority);
    }

    if (ferror(file)) {
        fprintf(stderr, "error: cannot read input file\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
