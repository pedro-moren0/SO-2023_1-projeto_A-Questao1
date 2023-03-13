#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "pdeque.h"
#include "process.h"


typedef struct item_t
{
    Process proc;
    struct item_t *next;
} item_t;

typedef struct pdeque_t
{
    int priority;
    item_t *start, *end;
} pdeque_t;



pdeque_t * create_empty_pdeque(int priority)
{
    pdeque_t *q = malloc(sizeof(pdeque_t));

    q->priority = priority;
    q->start = NULL;
    q->end = NULL;

    return q;
}

item_t * create_item(char* name, int burst, int priority, int waiting_time)
{
    item_t *item = malloc(sizeof(item_t));
    strcpy(item->proc.name, name);
    item->proc.cpu_burst = burst;
    item->proc.priority = priority;
    item->proc.waiting_time = waiting_time;
    item->next = NULL;

    return item;
}

void free_pdeque(pdeque_t *q)
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

int is_empty(pdeque_t *q)
{
    return q->start == NULL;
}

void print_pdeque(pdeque_t *q)
{
    item_t *tmp = q->start;
    int empty = is_empty(q);

    printf("Queue priority level: %d\n", q->priority);
    printf("Processes (Name, Priority, CPU Burst):\n");
    //imprime ate o ultimo item
    while(!empty && tmp != NULL)
    {
        printf("\t");
        print_proc(tmp->proc);
        tmp = tmp->next;
    }
}

void add_to_end(pdeque_t *q, Process p)
{
    item_t *novo = create_item(p.name, p.cpu_burst, p.priority, p.waiting_time);
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

void add_to_start(pdeque_t *q, Process p) {
    item_t *novo = create_item(p.name, p.cpu_burst, p.priority, p.waiting_time);
    if(is_empty(q))
    {
        q->start = novo;
        q->end = novo;
    }
    else
    {
        novo->next = q->start;
        q->start = novo;
    }
}

Process remove_from_end(pdeque_t *q)
{
    if(!is_empty(q))
    {
        item_t *tmp = q->start;

        // find penultimate item of queue
        while (tmp->next->next != NULL)
        {
            tmp = tmp->next;
        }
        Process p = q->end->proc;
        free(q->end);
        tmp->next = NULL;
        q->end = tmp;
        return p;
    }
    Process invalid = {
        .name = INVALID_PROCESS_NAME,
        .cpu_burst = INVALID_PROCESS_BURST,
        .priority = INVALID_PROCESS_PRIORITY,
        .waiting_time = INVALID_PROCESS_ARRIVAL_TIME
    };
    return invalid;
}

Process remove_from_start(pdeque_t *q)
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
        .waiting_time = INVALID_PROCESS_ARRIVAL_TIME
    };
    return invalid;
}
