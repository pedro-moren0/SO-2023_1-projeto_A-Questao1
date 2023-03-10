#ifndef PQUEUE_
#define PQUEUE_

#include "process.h"

typedef struct pqueue_t* Pqueue;

Pqueue create_empty_pqueue(int priority);
void free_pqueue(Pqueue q);
int is_empty(Pqueue q);
void print_pqueue(Pqueue q);
void enqueue(Pqueue q, Process p);
Process dequeue(Pqueue q);

#endif