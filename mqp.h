#ifndef MQP_
#define MQP_

#include "process.h"
#include "pqueue.h"

#define NUMBER_OF_PRIORITY_LEVELS 4

// typedef Pqueue[] MQP;

extern Process in_cpu;

void print_running_now();
void receive_procs(Process procs[], int procs_len, Pqueue mqp[]);

#endif