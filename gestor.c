#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include"gestor.h"

Tarefa tarefas[MAX];

void menu()
{
    printf("\n\t\t=== MENU DE TAREFAS ===\n");
    printf("\t\t1. Adicionar tarefa.\n");
    printf("\t\t2. Listar tarefas.\n");
    printf("\t\t3. Marcar como concluída.\n");
    printf("\t\t4. Excluir tarefa.\n");
    printf("\t\t5. Salvar em arquivo.\n");
    printf("\t\t7. Carregar arquivo.\n");
    printf("\t\t7. Mostrar menu.\n");
    printf("\t\t0. Sair\n");
}

int leropcao()
{
    int op;
    printf("\nEscolha uma opção acima: ");
    scanf("%d",&op);
    do
    {
        if(op<0||op>6)
        {
            printf("\nOpção invalida!\nIntroduza uma opção valida: ");
            scanf("%d",&op);
        }
    }
    while(op<0||op>6);
    return op;
}
int Sem_tarefa(int total)
{

    return total==0?1:0;
}
void adicionarTarefa(Tarefa tarefas[], int *total)//funcao para adicionar tarefa
{
    int aux=*total;
    printf("\nTarefa nº %d\n",aux+1);
    printf("Nome da tarefa: ");
    getchar(); // Limpa o \n do buffer do teclado
    fgets(tarefas[aux].descricao, 100, stdin);
    tarefas[aux].descricao[strcspn(tarefas[aux].descricao, "\n")] = '\0'; // remove o \n

    printf("Introduza o ID: ");
    scanf("%d", &tarefas[aux].id);

    printf("Status da tarefa (1 - concluída, 0 - não concluída): ");
    scanf("%d", &tarefas[aux].concluida);

    (*total)++;


}
void listarTarefas(Tarefa tarefas[], int total)
{
    int i;
    if(Sem_tarefa(total)){
        printf("Ainda não foram adicionadas tarefas ao sistema .\n");
        return;
        }
    for(i=0;i<total;i++)
    {
        printf("\nTarefa nº %d",i+1);
        printf("\nID : %d\n",tarefas[i].id);
        printf("Nome da tarefa : %s\n",tarefas[i].descricao);
        printf("Status da tarefa : %s\n\n",tarefas[i].concluida? "Concluída":"Não concluída");
    }


}
void marcarComoConcluida(Tarefa tarefas[], int total)
{
     if(Sem_tarefa(total)){
        printf("Ainda não foram adicionadas tarefas ao sistema .\n");
        return;
        }
    int ID,encontrou=0,i;
    printf("digite o ID da tarefa que deseja marcar como concluída: ");
    scanf("%d",&ID);
    for(i=0;i<total;i++)
    {
        if(ID==tarefas[i].id)
        {
            tarefas[i].concluida=1;
            encontrou=1;
            printf("Tarefa marcada como concluido !\n");
            break;
        }
    }
    if(!encontrou)
        printf("A tarefa com ID %d não foi encontrada.\n",ID);
}

void excluirTarefa(Tarefa tarefas[], int *total)
{
    int ID,encontrou=0,i,j;
     if(Sem_tarefa(*total)){
        printf("Ainda não foram adicionadas tarefas ao sistema .\n");
        return;
        }
    printf("Introduza o ID da tarefa para remover: ");
    scanf("%d",&ID);
    for(i=0;i<*total;i++)
    {
        if(ID==tarefas[i].id){
            encontrou=1;

            for(j=i;j<*total-1;j++)
                tarefas[j]=tarefas[j+1];
            (*total)--;
            printf("Tarefas com ID %d removida com sucesso!\n",ID);
            break;//como já encontrou e removeu, pode sair do loop
        }

    }
    if(!encontrou)
        printf("A tarefa com ID %d não existe no sistema \n",ID);

}
void salvarEmArquivo(Tarefa tarefas[], int total)
{
     if(Sem_tarefa(total)){
        printf("Ainda não foram adicionadas tarefas ao sistema .\n");
        return;
        }
    FILE *fp;
    int i;
    char nome[20];
    printf("Qual o nome do arquivo : ");
    scanf("%s",nome);
    fp=fopen(nome,"w");
    if(fp==NULL)
    {
        printf("Erro ao abrir o ficheiro para escrita.");
        exit(1);
    }

    fprintf(fp,"\t\t\nLista de Tarefas \n\n");
    for(i=0;i<total;i++)
    {
        fprintf(fp,"Tarefa nº%d\n",i+1);

        fprintf(fp,"ID : %d\nNome da tarefa : %s\nStatus da tarefa : %s\n",tarefas[i].id,tarefas[i].descricao,tarefas[i].concluida?"Concluída":"Não concluída");
        fprintf(fp,"\n");


    }
    fclose(fp);
    printf("Ficheiro Salvo  com sucesso!\n ");
}


void carregarDeArquivo(Tarefa tarefas[], int *total) {
    FILE *fp;
    char nome[50];
    char linha[200];
    int id, status;
    char descricao[100];
    int i = 0;

    printf("Nome do arquivo para carregar: ");
    scanf(" %s", nome);

    fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro para leitura.\n");
        return;
    }

    // Pula o cabeçalho "Lista de Tarefas"
    fgets(linha, sizeof(linha), fp); // \t\t
    fgets(linha, sizeof(linha), fp); // Lista de Tarefas
    fgets(linha, sizeof(linha), fp); // linha em branco

    while (fgets(linha, sizeof(linha), fp)) {
        // Lê "Tarefa nºX"
        if (strncmp(linha, "Tarefa nº", 9) != 0)
            continue;

        // Lê "ID : X"
        fgets(linha, sizeof(linha), fp);
        sscanf(linha, "ID : %d", &id);

        // Lê "Nome da tarefa : ..."
        fgets(linha, sizeof(linha), fp);
        sscanf(linha, "Nome da tarefa : %[^\n]", descricao);

        // Lê "Status da tarefa : ..."
        fgets(linha, sizeof(linha), fp);
        if (strstr(linha, "Concluída") != NULL)
            status = 1;
        else
            status = 0;

        // Pula linha em branco
        fgets(linha, sizeof(linha), fp);

        // Preenche vetor
        tarefas[i].id = id;
        tarefas[i].concluida = status;
        strcpy(tarefas[i].descricao, descricao);
        i++;
    }

    *total = i;
    fclose(fp);
    printf("Tarefa(s) carregada(s) com sucesso!\n");
}



