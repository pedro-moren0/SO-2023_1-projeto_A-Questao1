/*
 * Multilevel Queue Process (MQP) interface.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#ifndef MQP_
#define MQP_

#include "process.h"
#include "pdeque.h"

#define NUMBER_OF_PRIORITY_LEVELS 4 // as required in the
                                    // project's description

/*
 * Simulates the cpu function.
 * It is used to pass processes to it as if
 * the scheduler is assigning processes to the cpu
 */
extern Process in_cpu;

/*
 * MQP implementation.
 * Should not be modified directly to preserve the
 * simulational aspects. Can be passed as parameter.
 */
extern Pdeque mqp[];

/*
 * Prints the current process stored in in_cpu variable.
 *
 * Params: None
 * Return: None
 */
void print_running_now();

/*
 * Prints the internal state of MQP. Param should ideally be the
 * global variable mqp.
 *
 * Params: a MQP
 * Return: None
 */
void print_mqp(Pdeque mqp[]);

/*
 * Checks if all the queues in the MQP are empty.
 * Param should ideally be the global variable mqp.
 *
 * Params: a MQP
 * Return: 1 if MQP all MQP queues are empty, 0 otherwise
 */
int is_all_empty(Pdeque mqp[]);

/*
 * Process reception part of pipeline.
 * Distributes the processes in the MQP based on their
 * priorities. Uses SJF as tie breaker.
 *
 * Params: an array of Process, the array length, the MQP to
 *         distribute the processes
 * Return: None
 */
void receive_procs(Process procs[], int procs_len, Pdeque mqp[]);

/*
 * Dinamically allocates the Pqueue for each level in the
 * mqp global variable.
 *
 * Params: None
 * Return: None
 */
void initialize_mqp();

/*
 * Frees the dinamically allocated Pqueue in each level in the
 * mqp global variable.
 *
 * Params: None
 * Return: None
 */
void free_mqp();

/*
 * Threaded function to implement the aging policy in the MQP.
 * Every 10 seconds, the lowest priority processes is assigned
 * to the queue one level higher.
 *
 * Params: None
 * Return: None
 */
void *aging();

#endif