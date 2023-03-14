/*
 * Multilevel Queue Process implementation.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "mqp.h"
#include "pdeque.h"
#include "process.h"

#define AGING_INTERVAL 10 // as required in the
                          // project's description

/*
 * Simulates the cpu function.
 * It is used to pass processes to it as if
 * the scheduler is assigning processes to the cpu
 */
Process in_cpu;

/*
 * MQP implementation.
 * Should not be modified directly to preserve the
 * simulational aspects. Can be passed as parameter.
 */
Pdeque mqp[NUMBER_OF_PRIORITY_LEVELS];

/*
 * Prints the current process stored in in_cpu variable.
 *
 * Params: None
 * Return: None
 */
void print_running_now() {
    printf("Running in cpu: ");
    print_proc(in_cpu);
}

/*
 * Prints the internal state of MQP. Param should ideally be the
 * global variable mqp.
 *
 * Params: a MQP
 * Return: None
 */
void print_mqp(Pdeque mqp[]) {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        print_pdeque(mqp[i]);
        printf("\n");
    }
}

/*
 * Checks if all the queues in the MQP are empty.
 * Param should ideally be the global variable mqp.
 *
 * Params: a MQP
 * Return: 1 if MQP all MQP queues are empty, 0 otherwise
 */
int is_all_empty(Pdeque mqp[]) {
    int is_all_empty = 1;
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        is_all_empty = is_all_empty && is_empty(mqp[i]);
    }
    return is_all_empty;
}

/*
 * Process reception part of pipeline.
 * Distributes the processes in the MQP based on their
 * priorities. Uses SJF as tie breaker.
 *
 * Params: an array of Process, the array length, the MQP to
 *         distribute the processes
 * Return: None
 */
void receive_procs(Process procs[], int procs_len, Pdeque mqp[]) {
    // SJF policy
    insertion_sort_by_cpu_burst(procs, procs_len);  // overkill solution
    for (int i = 0; i < procs_len; i++)
    {
        add_to_end(mqp[procs[i].priority], procs[i]);
    }
}

/*
 * Dinamically allocates the Pqueue for each level in the
 * mqp global variable.
 *
 * Params: None
 * Return: None
 */
void initialize_mqp() {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        mqp[i] = create_empty_pdeque(i);
    }
}

/*
 * Frees the dinamically allocated Pqueue in each level in the
 * mqp global variable.
 *
 * Params: None
 * Return: None
 */
void free_mqp() {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        free_pdeque(mqp[i]);
    }
}

/*
 * Threaded function to implement the aging policy in the MQP.
 * Every 10 seconds, the lowest priority processes is assigned
 * to the queue one level higher.
 *
 * Params: None
 * Return: None
 */
void *aging() {
    int is_mqp_empty;
    while (1) {
        // Every operation over mqp is a critical section
        // thus it needs to be locked and unlock by mutex

        pthread_mutex_lock(m);
        is_mqp_empty = is_all_empty(mqp);
        pthread_mutex_unlock(m);

        if (is_mqp_empty) {  break; }

        sleep(AGING_INTERVAL);
        for (int i = NUMBER_OF_PRIORITY_LEVELS - 1; i > 0; i--) {
            pthread_mutex_lock(m);
            if (!(is_empty(mqp[i])))
            {
                Process p = remove_from_end(mqp[i]); // lowest priority process

                printf("\n*******\nPromoted ");
                print_proc(p);
                printf("*******\n");

                p.priority--; // decrements priority = ups a level in mqp
                add_to_end(mqp[i - 1], p); // sent to corresponding queue
                pthread_mutex_unlock(m);
                
                break; // start again from the lowest priority queue
            } else {
                pthread_mutex_unlock(m);
            }
        }
    }
    printf("exited thread\n");
    pthread_exit(NULL);
}