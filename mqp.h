#ifndef MQP_
#define MQP_

#include "process.h"
#include "pdeque.h"

#define NUMBER_OF_PRIORITY_LEVELS 4

extern Process in_cpu;
extern Pdeque mqp[];

void print_running_now();
void print_mqp(Pdeque mqp[]);
int is_all_empty(Pdeque mqp[]);
void receive_procs(Process procs[], int procs_len, Pdeque mqp[]);
void initialize_mqp();
void free_mqp();
void *aging();

#endif