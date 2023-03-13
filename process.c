#include <stdio.h>

#include "process.h"

void print_proc(Process p) {
    printf("%s, %d, %d\n",
        p.name, p.priority, p.cpu_burst);
}

void insertion_sort_by_cpu_burst(Process procs[], int procs_len) {
    for(int j = 1; j < procs_len; j++)
    {
        Process chave = procs[j];
        int i = j - 1;

        // insert chave in v[0..j-1 = i]
        while(i >= 0 && chave.cpu_burst < procs[i].cpu_burst)
        {
            procs[i + 1] = procs[i];
            i--;
        }
        procs[i + 1] = chave;
    }
}