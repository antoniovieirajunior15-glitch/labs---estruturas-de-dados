//Fazer programa para: Criar um arquivo texto com 20 chaves de números inteiros
// Em seguida percorrer a árvore inserindo no nó a sua altura (altura do nó na árvore).
// Exibir em pré ordem e em ordem simétrica, em cada linha, a chave do nó e sua altura.

#include <stdio.h>
#include <string.h>

typedef struct Nodo {
    int chave;
    int altura;
    struct Node* esq;
    struct Node* dir;
} Nodo;

Nodo* criar(int chave) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->chave = chave;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int calcularAltura(Nodo *raiz) {
    if (raiz == NULL) {
        return -1;
    }
    int he = calcularAltura(raiz->esq);
    int hd = calcularAltura(raiz->dir);
    raiz->altura = 1 + (he > hd ? he : hd);
    return raiz->altura;
}

void liberar(Nodo *raiz) {
    if (raiz != NULL) {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}
