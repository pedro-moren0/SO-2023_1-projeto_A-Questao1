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
        .cpu_burst = 190,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Firefox",
        .cpu_burst = 20,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Word",
        .cpu_burst = 100,
        .priority = 1,
        .waiting_time = 0
    },
    {
        .name = "PowerPoint",
        .cpu_burst = 120,
        .priority = 3,
        .waiting_time = 0
    },
    {
        .name = "GIMP",
        .cpu_burst = 80,
        .priority = 3,
        .waiting_time = 0
    },
    {
        .name = "definitivamente_nao_um_virus",
        .cpu_burst = 400,
        .priority = 0,
        .waiting_time = 0
    },
    {
        .name = "Visual Studio Code",
        .cpu_burst = 300,
        .priority = 1,
        .waiting_time = 0
    }
};