/*
 * Priority Double-Ended Queue (PDeque) interface
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#ifndef PQUEUE_
#define PQUEUE_

#include "process.h"

/*
 * Struct implementation of a PDeque.
 * The priority attribute is the priority associated with
 * that list, and the start and end attributes are pointers to the
 * start and end of the queue.
 */
typedef struct pdeque_t* Pdeque;

/*
 * Creates the root pointer to the PDeque via malloc.
 *
 * Params: the PDeque priority
 * Return: the root pointer to the PDeque
 */
Pdeque create_empty_pdeque(int priority);

/*
 * Frees the PDeque.
 *
 * Params: the root pointer to the PDeque
 * Return: None
 */
void free_pdeque(Pdeque q);

/*
 * Checks if the PDeque is empty.
 *
 * Params: the root pointer to the PDeque
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(Pdeque q);

/*
 * Formated print to the PDeque and its contents.
 *
 * Params: the root pointer to the PDeque
 * Return: None
 */
void print_pdeque(Pdeque q);

/*
 * Adds a Process to the end (last pos) of the PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: None
 */
void add_to_end(Pdeque q, Process p);

/*
 * Adds a Process to the start (first pos) of the PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: None
 */
void add_to_start(Pdeque q, Process p);

/*
 * Removes the Process at the end (last pos) of the PDeque.
 * If empty, returns a Process with invalid fields, and does
 * nothing to the provided PDeque.
 *
 * Params: the root pointer to the PDeque
 * Return: the removed Process if the PDeque is not empty, and
 *         a invalid Process otherwise.
 */
Process remove_from_end(Pdeque q);

/*
 * Removes the Process at the start (first pos) of the PDeque.
 * If empty, returns a Process with invalid fields, and does
 * nothing to the provided PDeque.
 *
 * Params: the root pointer to the PDeque, the Process to be added
 * Return: the removed Process if the PDeque is not empty, and
 *         a invalid Process otherwise.
 */
Process remove_from_start(Pdeque q);

#endif