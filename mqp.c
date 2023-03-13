#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "mqp.h"
#include "pdeque.h"
#include "process.h"

#define AGING_INTERVAL 10

Process in_cpu;
Pdeque mqp[NUMBER_OF_PRIORITY_LEVELS];


void print_running_now() {
    printf("Running in cpu: ");
    print_proc(in_cpu);
}

void print_mqp(Pdeque mqp[]) {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        print_pdeque(mqp[i]);
        printf("\n");
    }
}

int is_all_empty(Pdeque mqp[]) {
    int is_all_empty = 1;
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        is_all_empty = is_all_empty && is_empty(mqp[i]);
    }
    return is_all_empty;
}

void receive_procs(Process procs[], int procs_len, Pdeque mqp[]) {
    // SJF policy
    insertion_sort_by_cpu_burst(procs, procs_len);  // overkill solution
    for (int i = 0; i < procs_len; i++)
    {
        add_to_end(mqp[procs[i].priority], procs[i]);
    }
}

void initialize_mqp() {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        mqp[i] = create_empty_pdeque(i);
    }
}

void free_mqp() {
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        free_pdeque(mqp[i]);
    }
}

void *aging() {
    int is_mqp_empty;
    while (1) {
        printf("Testing break on t\n");

        pthread_mutex_lock(m);
        is_mqp_empty = is_all_empty(mqp);
        pthread_mutex_unlock(m);

        if (is_mqp_empty) {  break; }

        sleep(AGING_INTERVAL);
        for (int i = NUMBER_OF_PRIORITY_LEVELS - 1; i > 0; i--) {
            // printf("after sleep\n");
            pthread_mutex_lock(m);
            if (!(is_empty(mqp[i])))
            {
                Process p = remove_from_end(mqp[i]);
                printf("\n*******\nPromoted ");
                print_proc(p);
                printf("*******\n");
                p.priority--;
                add_to_end(mqp[i - 1], p); // decrements priority = ups a level in mqp
                pthread_mutex_unlock(m);
                
                break;
            } else {
                pthread_mutex_unlock(m);
            }
        }
    }
    printf("exited thread\n");
    pthread_exit(NULL);
}