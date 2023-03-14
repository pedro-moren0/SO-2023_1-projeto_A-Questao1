/*
 * Some processes to use in main.
 * Created for demonstration pourposes only.
 *
 * Pedro Moreno Silva.
 * Date: 14/03/2023
 * contact:    pedro.moreno@aluno.ufabc.edu.br
 */
#include "process.h"

int some_processes_len = 8;
Process some_processes[] = {
    {
        .name = "Paint",
        .cpu_burst = 1,
        .priority = 2,
        .waiting_time = 0
    },
    {
        .name = "Meujoguinho",
        .cpu_burst = 12,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Firefox",
        .cpu_burst = 6,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Word",
        .cpu_burst = 8,
        .priority = 1,
        .waiting_time = 0
    },
    {
        .name = "PowerPoint",
        .cpu_burst = 8,
        .priority = 3,
        .waiting_time = 0
    },
    {
        .name = "GIMP",
        .cpu_burst = 5,
        .priority = 3,
        .waiting_time = 0
    },
    {
        .name = "definitivamente_nao_um_virus",
        .cpu_burst = 30,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Visual Studio Code",
        .cpu_burst = 9,
        .priority = 1,
        .waiting_time = 0
    }
};