/*
 * Process functions implemententation.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#include <stdio.h>

#include "process.h"

/*
 * Formated print of a Process' contents.
 *
 * Params: the Process to print in stdout
 * Return: None
 */
void print_proc(Process p) {
    printf("%s, %d, %d\n",
        p.name, p.priority, p.cpu_burst);
}

/*
 * Orders an array of Process using the InsertionSort
 * algorithm and choosing the cpu_burst attribute as the
 * comparison key.
 * For more info see: https://pt.wikipedia.org/wiki/Insertion_sort
 *
 * Params: the Process array to be ordered, and its length
 * Return: None
 */
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

/*
 * Calculates the average waiting time over an array of Process
 *
 * Params: the Process array, and its length
 * Return: the average waiting time of the array
 */
float avg_waiting_time(Process procs[], int procs_len) {
    float sum = 0.0;
    for (int i = 0; i < procs_len; i++)
    {
        sum += (float) procs[i].waiting_time;
    }
    
    return sum / (float) procs_len;
}