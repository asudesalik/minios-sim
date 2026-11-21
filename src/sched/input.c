#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void free_processes(Process *processes, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        free(processes[i].bursts);
    }
    free(processes);
}

static int parse_number(const char *text, int minimum, int *result)
{
    char *end;
    if (text == NULL || !isdigit((unsigned char)text[0])) {
        return 0;
    }
    errno = 0;
    long value = strtol(text, &end, 10);
    if (errno != 0 || *end != '\0' || value < minimum || value > INT_MAX) {
        return 0;
    }
    *result = (int)value;
    return 1;
}

static int parse_process(char *line, Process *process)
{
    const char *separators = " \t\r\n";
    char *token = strtok(line, separators);

    if (token == NULL || token[0] != 'P' ||
        !parse_number(token + 1, 0, &process->pid) ||
        !parse_number(strtok(NULL, separators), 0, &process->arrival) ||
        !parse_number(strtok(NULL, separators), 0, &process->priority)) {
        return 0;
    }

    while ((token = strtok(NULL, separators)) != NULL) {
        int burst;
        if (!parse_number(token, 1, &burst)) {
            return 0;
        }
        int *grown = realloc(process->bursts,
                             (process->burst_count + 1) * sizeof(*grown));
        if (grown == NULL) {
            return 0;
        }
        process->bursts = grown;
        process->bursts[process->burst_count++] = burst;
    }

    if (process->burst_count == 0 || process->burst_count % 2 == 0) {
        return 0;
    }
    process->original_priority = process->priority;
    process->state = NEW;
    process->remaining = process->bursts[0];
    return 1;
}

static int read_line(FILE *file, char **line, size_t *capacity)
{
    size_t length = 0;
    int character;

    while ((character = fgetc(file)) != EOF) {
        if (length + 1 >= *capacity) {
            size_t next = *capacity == 0 ? 128 : *capacity * 2;
            char *grown = realloc(*line, next);
            if (grown == NULL) {
                return -1;
            }
            *line = grown;
            *capacity = next;
        }
        if (character == '\0') {
            return -1;
        }
        (*line)[length++] = (char)character;
        if (character == '\n') {
            break;
        }
    }

    if (ferror(file)) {
        return -1;
    }
    if (length == 0) {
        return 0;
    }
    (*line)[length] = '\0';
    return 1;
}

int read_process_file(const char *path, Process **processes, size_t *count)
{
    *processes = NULL;
    *count = 0;
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "error: cannot open input file\n");
        return 1;
    }

    char *line = NULL;
    size_t capacity = 0;
    int status;

    while ((status = read_line(file, &line, &capacity)) > 0) {
        char *start = line;
        while (isspace((unsigned char)*start)) {
            start++;
        }
        if (*start == '\0' || *start == '#') {
            continue;
        }

        Process process = {0};
        if (!parse_process(start, &process)) {
            free(process.bursts);
            status = -1;
            break;
        }
        for (size_t i = 0; i < *count; i++) {
            if ((*processes)[i].pid == process.pid) {
                status = -1;
            }
        }
        Process *grown = status < 0 ? NULL :
            realloc(*processes, (*count + 1) * sizeof(*grown));
        if (grown == NULL) {
            free(process.bursts);
            status = -1;
            break;
        }
        *processes = grown;
        (*processes)[(*count)++] = process;
    }

    free(line);
    fclose(file);
    if (status < 0 || *count == 0) {
        free_processes(*processes, *count);
        *processes = NULL;
        *count = 0;
        fprintf(stderr, "error: invalid input or insufficient memory\n");
        return 1;
    }
    return 0;
}
