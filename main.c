/*
 * Process scheduler simulation main application.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mqp.h"
#include "pdeque.h"
#include "process.h"
#include "some_processes.h"

pthread_mutex_t *m; // mutex pointer

int main(int argc, char const *argv[])
{
    pthread_t aging_tid; // id of thread that runs age func
    int err; // stores thread creation status

    m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);

    initialize_mqp();

    // Process history to check results after
    Process history[some_processes_len];
    int history_pos = 0;

    // Process reception part of pipeline
    receive_procs(some_processes, some_processes_len, mqp);

    int elapsed_time = 0;
    
    printf("MQP before execution start:\n");
    print_mqp(mqp);

    err = pthread_create(&aging_tid, NULL, aging, NULL);
    // Case failed to create the thread
    if (err != 0) {
        fprintf(stderr, "Failed to create thread. Aborting.\n");
        free_mqp();
        pthread_mutex_destroy(m);
        return 1;
    } else {
        printf("Created thread\n");
    }

    // Process scheduling part of pipeline
    // Fetches all processes in mqp to cpu
    int is_mqp_empty;
    while (1)
    {
        // Every operation over mqp is a critical section
        // thus it needs to be locked and unlock by mutex

        pthread_mutex_lock(m);
        is_mqp_empty = is_all_empty(mqp);
        pthread_mutex_unlock(m);

        if (is_mqp_empty) {  break; }
        
        for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
        {
            pthread_mutex_lock(m);
            if (!(is_empty(mqp[i])))
            {
                printf("--------------------------------------------------------\n");

                // sends highest priority process to the cpu
                in_cpu = remove_from_start(mqp[i]);
                pthread_mutex_unlock(m);
                in_cpu.waiting_time += elapsed_time;

                printf("Elapsed time: %d seconds\n", elapsed_time);
                print_running_now();
                printf("\n");
                sleep(in_cpu.cpu_burst); // simulates processing time

                // prints mqp internal state
                printf("MQP contents:\n");
                pthread_mutex_lock(m);
                print_mqp(mqp);
                pthread_mutex_unlock(m);

                // updates history with finished process
                history[history_pos++] = in_cpu;
                elapsed_time += in_cpu.cpu_burst;

                break; // start again from the highest priority queue
            } else {
                pthread_mutex_unlock(m);
            }
        }
    }
    
    pthread_join(aging_tid, NULL);

    // Show results part of the pipeline
    // Prints processes run in order with respec. waiting times
    printf("--------------------------------------------------------\n");
    printf("History of run processes(name, priority, cpu burst):\n");
    for (int i = 0; i < some_processes_len; i++)
    {
        printf("Waiting time of %d s for ", history[i].waiting_time);
        print_proc(history[i]);
    }
    printf("Average waiting time: %.3f seconds\n", avg_waiting_time(history, some_processes_len));

    free_mqp();
    pthread_mutex_destroy(m);
    return 0;
}
