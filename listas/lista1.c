#include <stdio.h>
#include <string.h>

//1) Escrever algoritmo para criar uma árvore binária e inserir nó na árvore (sempre completa ou cheia).
//a. A partir de números gerados aleatoriamente.

typedef struct no {
    int valor;
    struct no *esq;
    struct no *dir;
} noarv;

noarv* criar_no(int num) {
    noarv *aux = (noarv*)malloc(sizeof(noarv));
    aux->valor = num;
    aux->esq = NULL;
    aux->dir = NULL;
    return aux;
}

noarv* inserir_A(noarv* raiz, int num) {
    if (raiz == NULL) {
        return criar_no(num);
    }
    noarv* fila[100];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = raiz; // Coloca a raiz na fila

    while (inicio < fim) {
        noarv* atual = fila[inicio++]; // Retira o primeiro nó da fila

        // Tenta inserir na esquerda[cite: 1]
        if (atual->esq == NULL) {
            atual->esq = criar_no(num);
            return raiz;
        } else {
            fila[fim++] = atual->esq;
        }

        // Tenta inserir na direita[cite: 1]
        if (atual->dir == NULL) {
            atual->dir = criar_no(num);
            return raiz;
        } else {
            fila[fim++] = atual->dir;
        }
    }

    return raiz;
}
//b. A partir de um vetor previamente inicializado (neste caso para testes não precisa ser completa ou cheia).
noarv* inserir_B(noarv* raiz, int num) {
    if (raiz == NULL) {
        noarv *aux = (noarv*)malloc(sizeof(noarv));
        aux->valor = num;
        aux->esq = NULL;
        aux->dir = NULL;
        return aux;
    } else {
        if (num < raiz->valor) {
            raiz->esq = inserir_versao1(raiz->esq, num);
        } else {
            raiz->dir = inserir_versao1(raiz->dir, num);
        }
        return raiz;
    }
}