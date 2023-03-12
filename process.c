#include <stdio.h>

#include "process.h"

void print_proc(Process p) {
    printf("%s, %d, %d - Arrival time: %d\n",
        p.name, p.priority, p.cpu_burst, p.arrival);
}