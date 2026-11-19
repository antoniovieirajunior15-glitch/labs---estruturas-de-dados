#include <stdio.h>
#include <stdlib.h>
#include "TAD.c" 

int main(void){
    ListaTP* lista = criaLista();
    printf("ola torcedor\n");
    int opcao;
    char categoria;
    int senha;
    do{
        printf("MENU DE ATENDIMENTO\n");
        printf("1. Inserir torcedor\n");
        printf("2. Remover torcedor\n");
        printf("3. Exibir fila atual\n");
        printf("-1. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite sua categoria (A, B ou G): \n");
                scanf(" %c", &categoria);
                while (categoria != 'A' && categoria != 'B' && categoria != 'G') {
                    printf("Categoria invalida, tente novamente\n");
                    printf("Digite sua categoria (A, B ou G): \n");
                    scanf(" %c", &categoria);
                }
                senha = insereNaLista(lista, categoria);
                printf("Torcedor %d-%c inserido com sucesso!\n", senha, categoria);
                break;
            case 2:
                printf("Informe a senha do torcedor a remover: ");
                scanf("%d", &senha);
                if (RemoveDaLista(lista, senha)) {
                    printf("Torcedor com senha %d removido com sucesso.\n", senha);
                }
                exibeLista(lista);
                break;
            case 3:
                exibeLista(lista);
                break;
            case -1:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != -1);
    freeElementoDaLista(lista);
    return 0;
}