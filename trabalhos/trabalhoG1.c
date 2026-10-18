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