#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include"gestor.h"

int main()
{
    setlocale(LC_ALL,"Portuguese");
    Tarefa tarefa[MAX];
    int total=0;
    int opcao;
    menu();
    do
    {
        opcao=leropcao();//lê e devolve uma opcao valida
        switch(opcao)
        {
            case 1:
                adicionarTarefa(tarefa,&total);
                break;
            case 2:
                listarTarefas(tarefa,total);
                break;
            case 3:
                marcarComoConcluida(tarefa,total);
                break;
            case 4:
                excluirTarefa(tarefa, &total);
                break;
            case 5:
                salvarEmArquivo(tarefa,total);
                break;
            case 6:
                carregarDeArquivo(tarefa,&total);
                break;


            case 7:
                system("CLS");//limpar oterminar
                printf("Tela limpa. A seguir, o menu seráexibido:\n");
                menu();
                break;
            default:
                 system("CLS");
                 break;


        }
    }while(opcao);

    printf("Saindo.....\n");
    return 0;
}
