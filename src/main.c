#include <stdio.h>

int main(void)
{
    FILE *file = fopen("tests/sched_io.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "error: cannot open input file\n");
        return 1;
    }

    int character;

    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    fclose(file);
    return 0;
}