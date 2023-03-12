#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "pqueue.h"
#include "process.h"


typedef struct item_t
{
    Process proc;
    struct item_t *next;
} item_t;

typedef struct pqueue_t
{
    int priority;
    item_t *start, *end;
} pqueue_t;



pqueue_t * create_empty_pqueue(int priority)
{
    pqueue_t *q = malloc(sizeof(pqueue_t));

    q->priority = priority;
    q->start = NULL;
    q->end = NULL;

    return q;
}

item_t * create_item(char* name, int burst, int priority, int arrival)
{
    item_t *item = malloc(sizeof(item_t));
    strcpy(item->proc.name, name);
    item->proc.cpu_burst = burst;
    item->proc.priority = priority;
    item->proc.arrival = arrival;
    item->next = NULL;

    return item;
}

void free_pqueue(pqueue_t *q)
{
    item_t *current = q->start, *previous = NULL;
    while(current != NULL)
    {
        previous = current;
        current = current->next;
        free(previous);
    }
    free(q);
}

int is_empty(pqueue_t *q)
{
    return q->start == NULL;
}

void print_pqueue(pqueue_t *q)
{
    item_t *tmp = q->start;
    int empty = is_empty(q);

    printf("Queue priority level: %d\n", q->priority);
    printf("Processes:\n");
    //imprime ate o ultimo item
    while(!empty && tmp != NULL)
    {
        printf("\t");
        print_proc(tmp->proc);
        tmp = tmp->next;
    }
}

void enqueue(pqueue_t *q, Process p)
{
    item_t *novo = create_item(p.name, p.cpu_burst, p.priority, p.arrival);
    if(is_empty(q))
    {
        q->start = novo;
        q->end = novo;
    }
    else
    {
        q->end->next = novo;
        q->end = novo;
    }
}

Process dequeue(pqueue_t *q)
{
    if(!is_empty(q))
    {
        item_t *tmp = q->start;
        Process p = tmp->proc;
        q->start = tmp->next;
        free(tmp);
        return p;
    }
    Process invalid = {
        .name = INVALID_PROCESS_NAME,
        .cpu_burst = INVALID_PROCESS_BURST,
        .priority = INVALID_PROCESS_PRIORITY,
        .arrival = INVALID_PROCESS_ARRIVAL_TIME
    };
    return invalid;
}
