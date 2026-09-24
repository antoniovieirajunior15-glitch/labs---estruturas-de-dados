//Fazer programa para percorrer a árvore por nível (use uma fila auxiliar) exibindo a chave e o nível
#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int chave;
    struct nodo *esq;
    struct nodo *dir;
};
typedef struct nodo Nodo;

typedef struct itemFila {
    Nodo *no;
    int nivel;
    struct itemFila *prox;
} ItemFila;

typedef struct {
    ItemFila *inicio;
    ItemFila *fim;
} Fila;

void filaInicializa(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(Fila *f) {
    return f->inicio == NULL;
}

void filaEnfileira(Fila *f, Nodo *no, int nivel) {
    ItemFila *novo = (ItemFila *) malloc(sizeof(ItemFila));
    novo->no = no;
    novo->nivel = nivel;
    novo->prox = NULL;

    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void filaDesenfileira(Fila *f, Nodo **noOut, int *nivelOut) {
    ItemFila *removido = f->inicio;
    *noOut = removido->no;
    *nivelOut = removido->nivel;

    f->inicio = removido->prox;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(removido);
}

Nodo *criaNodo(int chave) {
    Nodo *novo = (Nodo *) malloc(sizeof(Nodo));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

Nodo *insere(Nodo *raiz, int chave) {
    if (raiz == NULL) {
        return criaNodo(chave);
    }
    if (chave < raiz->chave) {
        raiz->esq = insere(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = insere(raiz->dir, chave);
    }
    return raiz;
}

void preOrdem(Nodo *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->chave);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

void emOrdem(Nodo *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->chave);
    emOrdem(raiz->dir);
}

void porNivel(Nodo *raiz) {
    Fila f;
    Nodo *atual;
    int nivelAtual;

    filaInicializa(&f);
    if (raiz == NULL) return;

    filaEnfileira(&f, raiz, 0);

    while (!filaVazia(&f)) {
        filaDesenfileira(&f, &atual, &nivelAtual);
        printf("%d(%d) ", atual->chave, nivelAtual);

        if (atual->esq != NULL) {
            filaEnfileira(&f, atual->esq, nivelAtual + 1);
        }
        if (atual->dir != NULL) {
            filaEnfileira(&f, atual->dir, nivelAtual + 1);
        }
    }
}

void liberaArvore(Nodo *raiz) {
    if (raiz == NULL) return;
    liberaArvore(raiz->esq);
    liberaArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    const char *nomeArquivo = "entrada.txt";
    FILE *arquivo;
    Nodo *raiz = NULL;
    int chave;

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'\n", nomeArquivo);
        return 1;
    }

    while (fscanf(arquivo, "%d", &chave) == 1) {
        raiz = insere(raiz, chave);
    }
    fclose(arquivo);

    printf("Por nivel: ");
    porNivel(raiz);
    printf("\n");

    printf("Pre-ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Simetrica: ");
    emOrdem(raiz);
    printf("\n");

    liberaArvore(raiz);
    return 0;
}
