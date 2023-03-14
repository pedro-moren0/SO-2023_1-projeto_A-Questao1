# Questão 1 - Projeto A
## Sistemas Operacionais - 2023.1 - UFABC

### Descrição
Neste exercício foi proposto realizar uma simulação de um escalonador de processos usando _Multilevel Queue Process_ (MQP) com 4 níveis (0 o mais prioritário até 3, menos prioritário). Cada processo obrigatoriamente deveria ter um nome, uma duração de cpu burst, e uma prioridade associados a ele. Todos os processos chegariam ao mesmo tempo ao escalonador, e so haveria uma cpu disponível para o escalonamento. No admissão dos processos no MQP, processos de prioridade idêntica deveriam ser diferenciados por Shortest Job First (SJF). Além disso, uma função de _aging_ deveria aumentar em 1 a prioridade do processo menos prioritário a cada 10 segundos. Após enviar todos os processos a cpu, os resultados deveriam ser apresentados, isto é, o _waiting time_ de cada processo.

### Implementação
Primeiramente, escolhi tratar a lista de processos com um algoritmo de ordenação antes de atribuir cada item a MQP para garantir que o desempate por SJF acontecesse primeiro. A escolha do insertionSort para essa tarefa foi por conta de afinidade.

Para a implementação, escolhi projetar a MQP utilizando deques (_Double Ended Queue_) pela possibilidade de operar em ambas as pontas da fila (por conveniência, já que o _aging_ requer promover o processo menos prioritário, que por sua vez fica no início de cada fila). O deque, por sua vez, foi implementado usando listas ligadas alocadas dinamicamente. O motivo por essa escolha foi por simular o uso de memória que ocorre cada vez que o SO instancia um novo processo.

Finalmente, para executar o _aging_, utilizei uma thread para que, ao mesmo tempo que fosse passado um processo para a CPU, paralelamente o processo menos prioritário pudesse ser promovido. Isso também permite que qualquer valor seja escolhido para o cpu burst dos processos, e não só multiplos de 10. Para contornar a concorrência no MQP, utilizamos o Mutex da biblioteca `pthread`.

### Instalação
(Linux) Em uma pasta de sua preferência, basta abrir um terminal e fazer:

`$ git clone https://github.com/pedro-moren0/SO-2023_1-projeto_A-Questao1`

`$ make`

`$ ./mqp_scheduler`