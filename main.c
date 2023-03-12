#include <stdio.h>

#include "mqp.h"
#include "pqueue.h"
#include "process.h"

int main(int argc, char const *argv[])
{
    Pqueue mqp[NUMBER_OF_PRIORITY_LEVELS];
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        mqp[i] = create_empty_pqueue(i);
    }
    
    Process procs[] = {
        {
            .name = "Paint",
            .cpu_burst = 1,
            .priority = 2,
            .arrival = 0
        },
        {
            .name = "Meujoguinho",
            .cpu_burst = 190,
            .priority = 0,
            .arrival = 0
        },
        {
            .name = "Firefox",
            .cpu_burst = 20,
            .priority = 0,
            .arrival = 0
        }
    };

    receive_procs(procs, 3, mqp);

    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        print_pqueue(mqp[i]);
        printf("\n");
    }
    
    in_cpu = dequeue(mqp[0]);
    print_running_now();
    
    for (int i = 0; i < NUMBER_OF_PRIORITY_LEVELS; i++)
    {
        print_pqueue(mqp[i]);
    }
    return 0;
}
