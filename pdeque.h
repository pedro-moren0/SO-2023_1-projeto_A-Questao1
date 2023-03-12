#ifndef PQUEUE_
#define PQUEUE_

#include "process.h"

typedef struct pdeque_t* Pdeque;

Pdeque create_empty_pdeque(int priority);
void free_pdeque(Pdeque q);
int is_empty(Pdeque q);
void print_pdeque(Pdeque q);
void add_to_end(Pdeque q, Process p);
void add_to_start(Pdeque q, Process p);
Process remove_from_end(Pdeque q);
Process remove_from_start(Pdeque q);


#endif