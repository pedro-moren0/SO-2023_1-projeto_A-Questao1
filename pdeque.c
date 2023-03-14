/*
 * Priority Double-Ended Queue (PDeque) implementation
 * (implemented with linked lists).
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "pdeque.h"
#include "process.h"

/*
 * Struct implementation of an item in the
 * queue. The proc attribute is the Process the item
 * holds, and the next attribute is a pointer that points
 * to the next item in the sequence.
 */
typedef struct item_t
{
    Process proc;
    struct item_t *next;
} item_t;

/*
 * Struct implementation of a PDeque.
 * The priority attribute is the priority associated with
 * that list, and the start and end attributes are pointers to the
 * start and end of the queue.
 */
typedef struct pdeque_t
{
    int priority;
    item_t *start, *end;
} pdeque_t;


/*
 * Creates the root pointer to the PDeque via malloc.
 *
 * Params: the PDeque priority
 * Return: the root pointer to the PDeque
 */
pdeque_t * create_empty_pdeque(int priority)
{
    pdeque_t *q = malloc(sizeof(pdeque_t));

    q->priority = priority;
    q->start = NULL;
    q->end = NULL;

    return q;
}

/*
 * Creates the an item of the PDeque via malloc.
 *
 * Params: the Process paramenters (name, cpu burst duration,
 *         priority and its waiting time)
 * Return: a pointer to the item created
 */
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

/*
 * Frees the PDeque.
 *
 * Params: the root pointer to the PDeque
 * Return: None
 */
void free_pdeque(pdeque_t *q)
{
    item_t *current = q->start, *previous = NULL;

    // first frees items, them frees root
    while(current != NULL)
    {
        previous = current;
        current = current->next;
        free(previous);
    }
    free(q);
}

/*
 * Checks if the PDeque is empty.
 *
 * Params: the root pointer to the PDeque
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(pdeque_t *q)
{
    return q->start == NULL;
}

/*
 * Formated print to the PDeque and its contents.
 *
 * Params: the root pointer to the PDeque
 * Return: None
 */
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

/*
 * Adds a Process to the end (last pos) of the PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: None
 */
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

/*
 * Adds a Process to the start (first pos) of the PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: None
 */
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

/*
 * Removes the Process at the end (last pos) of the PDeque.
 * If empty, returns a Process with invalid fields, and does
 * nothing to the provided PDeque.
 *
 * Params: the root pointer to the PDeque
 * Return: the removed Process if the PDeque is not empty, and
 *         a invalid Process otherwise.
 */
Process remove_from_end(pdeque_t *q)
{
    if(!is_empty(q))
    {
        item_t *tmp = q->start;
        if (tmp->next == NULL) // case deque has only one element
        {
            Process p = q->end->proc;
            free(q->end);
            q->start = q->end = NULL;
            return p;
        } else {
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
    }
    // case empty deque
    Process invalid = {
        .name = INVALID_PROCESS_NAME,
        .cpu_burst = INVALID_PROCESS_BURST,
        .priority = INVALID_PROCESS_PRIORITY,
        .waiting_time = INVALID_PROCESS_ARRIVAL_TIME
    };
    return invalid;
}

/*
 * Removes the Process at the start (first pos) of the PDeque.
 * If empty, returns a Process with invalid fields, and does
 * nothing to the provided PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: the removed Process if the PDeque is not empty, and
 *         a invalid Process otherwise.
 */
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
