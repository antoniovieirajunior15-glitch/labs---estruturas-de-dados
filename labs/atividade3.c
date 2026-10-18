//Fazer funções em linguagem C para:
//a)deve inverter as sub árvores de cada nó.
//tambem deve exibir em pré ordem e em ordem simétrica os nós da árvores (endereço do nó, chave e ponteiros).
//b) Criar um arquivo texto com 20 chaves de números inteiros:
//Em seguida o programa deve inserir em cada nó o número de nós que ela possui (incluindo a raiz da sub-árvore).
//deve exibir em pré ordem e em ordem simétrica os nós da árvores (endereço do nó, chave e ponteiros).
#include <stdio.h>
#include <string.h>

//letra A)
typedef struct nodo Nodo;
struct nodo {
	int chave;
	int nnos;
	struct nodo* esq;
	struct nodo* dir;
};

Nodo* inverterSubArvore(Nodo* raiz) {
	if (raiz == NULL) {
		return NULL;
	}
	Nodo* temporario = raiz->esq;

	raiz->esq = raiz->dir;
	raiz->dir = temporario;

	inverterSubArvore(raiz->esq);
	inverterSubArvore(raiz->dir);

	return raiz;
}
//letra B)

Nodo* criaNo(int chave) {
	Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	if (novo == NULL) {
		exit(1);
	}
	novo->chave = chave;
	novo->nnos = 1;
	novo->esq = NULL;
	novo->dir = NULL;
	return novo;
}

Nodo* inserir(Nodo* raiz, int chave) {
	if (raiz == NULL) {
		return 1;
	};
	if (chave < raiz->chave)
		raiz->esq = insere(raiz->esq, chave);
	else if (chave > raiz->chave)
		raiz->dir = insere(raiz->dir, chave);

	return raiz;
}
