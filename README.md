# MiniOS-Sim

An operating system simulator written in C for an individual course project.

## Current progress

The input module loads processes and their CPU/I/O bursts into a dynamically
allocated list. It rejects invalid numbers, duplicate process IDs, and missing
or invalid burst sequences. The current main program displays the records from
`tests/sched_io.txt`; command-line selection and scheduling are not implemented yet.

## Build and run

```sh
make
./minios
```

Remove the generated executable with `make clean`.

The project targets Ubuntu 24.04. The initial build has been checked on macOS;
Ubuntu validation is pending.
