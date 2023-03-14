/*
 * Process interface.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#ifndef PROCESS_
#define PROCESS_


#define PROCESS_NAME_MAXIMUM_LENGTH 50 // arbitrary, can be changed

// constants to use when a "null process" is required 
#define INVALID_PROCESS_NAME "INVALID PROCESS NAME"
#define INVALID_PROCESS_BURST -1
#define INVALID_PROCESS_PRIORITY -1
#define INVALID_PROCESS_ARRIVAL_TIME -1

/*
 * Struct implementation of a Process.
 * The attributes are a name with 50 charac max,
 * the cpu burst time length, the priority of the process,
 * and its waiting time to be sent to the cpu.
 */
typedef struct tProcess
{
    char name[PROCESS_NAME_MAXIMUM_LENGTH];
    int cpu_burst;
    int priority;
    int waiting_time;
} Process;

/*
 * Formated print of a Process' contents.
 *
 * Params: the Process to print in stdout
 * Return: None
 */
void print_proc(Process p);

/*
 * Orders an array of Process using the InsertionSort
 * algorithm and choosing the cpu_burst attribute as the
 * comparison key.
 *
 * Params: the Process array to be ordered, and its length
 * Return: None
 */
void insertion_sort_by_cpu_burst(Process procs[], int procs_len);

/*
 * Calculates the average waiting time over an array of Process
 *
 * Params: the Process array, and its length
 * Return: the average waiting time of the array
 */
float avg_waiting_time(Process procs[], int procs_len);

#endif