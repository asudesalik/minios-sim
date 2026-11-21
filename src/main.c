#include <stdio.h>

int main(void)
{
    FILE *file = fopen("tests/sched_io.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "error: cannot open input file\n");
        return 1;
    }

    char line[1024];

while (fgets(line, sizeof(line), file) != NULL) {
    if (line[0] == '#' || line[0] == '\n') {
        continue;
    }

    printf("%s", line);
}

    fclose(file);
    return 0;
}