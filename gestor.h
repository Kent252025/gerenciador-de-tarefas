#ifndef GESTOR_H_INCLUDED
#define GESTOR_H_INCLUDED

#define MAX 100

typedef struct {
    int id;
    char descricao[100];
    int concluida;
} Tarefa;




void menu();

int leropcao();
int Sem_tarefa(int total);

void adicionarTarefa(Tarefa tarefas[], int *total);

void listarTarefas(Tarefa tarefas[], int total);

void marcarComoConcluida(Tarefa tarefas[], int total);

void excluirTarefa(Tarefa tarefas[], int *total);

void salvarEmArquivo(Tarefa tarefas[], int total);

void carregarDeArquivo(Tarefa tarefas[], int *total);


#endif // GESTOR_H_INCLUDED
