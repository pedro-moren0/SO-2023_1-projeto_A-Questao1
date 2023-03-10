#ifndef PROCESS_
#define PROCESS_


#define PROCESS_NAME_MAXIMUM_LENGTH 50

#define INVALID_PROCESS_NAME "INVALID PROCESS NAME"
#define INVALID_PROCESS_BURST -1
#define INVALID_PROCESS_PRIORITY -1


typedef struct tProcess
{
    char name[PROCESS_NAME_MAXIMUM_LENGTH];
    int cpu_burst;
    int priority;
} Process;


void print_proc(Process p);


#endif