#include <stdio.h>

#include "pqueue.h"
#include "process.h"

int main(int argc, char const *argv[])
{
    /*
    Process p = {
        .name = "Paint",
        .cpu_burst = 10,
        .priority = 1
    };
    print_proc(p);
    */
   
    Pqueue f = create_empty_pqueue(1);
    enqueue(f, (Process){"Paint", 1, 2});
    enqueue(f, (Process){"Meujoguinho", 190, 0});
    enqueue(f, (Process){"Firefox", 20, 0});
    print_pqueue(f);
    print_proc(dequeue(f));
    printf("\n");
    //enqueue(f, (Process){"my_prog", 5, 3});
    print_pqueue(f);
    print_proc(dequeue(f));
    printf("\n");
    print_proc(dequeue(f));
    printf("\n");
    print_proc(dequeue(f));
    printf("\n");
    print_proc(dequeue(f));
    printf("\n");
    print_proc(dequeue(f));
    printf("\n");
    free_pqueue(f);
    return 0;
}
