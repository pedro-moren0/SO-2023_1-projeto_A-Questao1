#include <stdio.h>

#include "mqp.h"
#include "pqueue.h"
#include "process.h"

Process in_cpu;

void print_running_now() {
    printf("Running in cpu: ");
    print_proc(in_cpu);
}

void receive_procs(Process procs[], int procs_len, Pqueue mqp[]) {
    for (int i = 0; i < procs_len; i++)
    {
        enqueue(mqp[procs[i].priority], procs[i]);
    }
}