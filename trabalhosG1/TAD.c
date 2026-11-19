#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct torcedor Torcedor;
struct torcedor {
    int numFila;         
    char categoria;     
    Torcedor* prox;      
};

typedef struct ListaTorcedoresPrioridade ListaTP;
struct ListaTorcedoresPrioridade {
    Torcedor* primeiroDaFila; 
    int ultimaSenhaGerada;     
    int qtdA;                  
    int qtdB;                  
    int qtdG;                  
};

ListaTP* criaLista(void) { 

	ListaTP* novaLista = (ListaTP*)malloc(sizeof(ListaTP));
	if (novaLista == NULL) {
		printf("Erro ao alocar nova Lista");
		exit(1);
	}
	novaLista->primeiroDaFila = NULL;
	novaLista->ultimaSenhaGerada = 0;
	novaLista->qtdA = 0;
	novaLista->qtdB = 0;
	novaLista->qtdG = 0;
	return novaLista;

}
//a) Torcedores chegando na fila de atendimento (entrada de dados): “i” significa incluir. 
//Vamos supor que existam N postos de atendimento, então podem estar sendo
//atendidos, em um dado momento, toda a fila.

int insereNaLista(ListaTP* Lista, char categoria) {
	Torcedor* novoTorcedor;
	Torcedor* torcedorAtual;
	Torcedor* torcedorAnt =NULL;
	novoTorcedor = (Torcedor*)malloc(sizeof(Torcedor));
	if (novoTorcedor == NULL) {
		printf("Erro de memoria\n");
		exit(1);
	}                  
	novoTorcedor->numFila = ++Lista->ultimaSenhaGerada; 
	novoTorcedor->categoria = categoria;
	torcedorAtual = Lista->primeiroDaFila;
	while (torcedorAtual != NULL && torcedorAtual->categoria <= categoria) {
		torcedorAnt = torcedorAtual;
		torcedorAtual = torcedorAtual->prox;
	}
	novoTorcedor->prox = torcedorAtual;
	if (torcedorAnt == NULL) {
		Lista->primeiroDaFila = novoTorcedor;
	}
	else {
		torcedorAnt->prox = novoTorcedor;
	}

	if (categoria == 'A') {
		Lista->qtdA++;
	}
	else{
		if (categoria == 'B') {
			Lista->qtdB++;
		}
		else {
			Lista->qtdG++;
		}	
	}
	

	return novoTorcedor->numFila;
}


//b) Então, em um dado momento, devem ser excluídos da lista os torcedores atendidos(entrada de dados): “e” significa excluir
int RemoveDaLista(ListaTP* Lista, int senha) {
	Torcedor* torcedorAtual = Lista->primeiroDaFila;
	Torcedor* torcedorAnt = NULL;

	while (torcedorAtual != NULL && torcedorAtual->numFila != senha) {
		torcedorAnt = torcedorAtual;
		torcedorAtual = torcedorAtual->prox;
	}

	if (torcedorAtual == NULL) {
		printf("Torcedor a ser removido nao existe na fila\n");
		return 0;
	}
	char temp = torcedorAtual->categoria;

	if (torcedorAnt == NULL) {
		Lista->primeiroDaFila = torcedorAtual->prox;
	} else {
		torcedorAnt->prox = torcedorAtual->prox;
	}
	if (temp == 'A') {
		Lista->qtdA--;
	} else if (temp == 'B') {
		Lista->qtdB--;
	} else if (temp == 'G') {
		Lista->qtdG--;
	}
	free(torcedorAtual);

	return 1;
}
//C) e D)
void exibeLista(ListaTP* Lista) {
    if (Lista == NULL) {
        return;
    }
    int total = Lista->qtdA + Lista->qtdB + Lista->qtdG;

    printf("Total: %d - A: %d B: %d G: %d\n", total, Lista->qtdA, Lista->qtdB, Lista->qtdG);

    Torcedor* atual = Lista->primeiroDaFila;
    while (atual != NULL) {
        printf("%d-%c\n", atual->numFila, atual->categoria);
        atual = atual->prox;
    }
}

void freeElementoDaLista(ListaTP *Lista) {
	Torcedor* Atual = Lista->primeiroDaFila;
	Torcedor* Ant = NULL;

	while (Atual != NULL) {
		Ant = Atual;
		Atual = Atual->prox;
		free(Ant);
	}
	free(Lista);
	return;
}

