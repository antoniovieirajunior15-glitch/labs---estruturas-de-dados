/*
 * Busca em Profundidade (DFS) a partir do no 8
 * Programa separado - usa o mesmo grafo do trabalho.
 */
#include <stdio.h>
#include <stdlib.h>

#define N 9          /* vertices 0 a 8 */
#define M 14         /* arestas */

typedef struct { int u, v, w; } Aresta;

static Aresta arestas[M] = {
    {0, 1, 4},  {0, 7, 8},  {1, 2, 8},  {1, 7, 11},
    {2, 3, 7},  {2, 8, 2},  {2, 5, 4},  {3, 4, 9},
    {3, 5, 14}, {4, 5, 10}, {5, 6, 2},  {6, 7, 1},
    {6, 8, 6},  {7, 8, 7}
};

static int matriz[N][N];
static int visitado[N], pred[N], desc[N], fim[N], ordem[N];
static int tempo = 0, qtd = 0;

static void construirMatriz(void) {
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) matriz[i][j] = 0;   /* 0 = sem aresta */
    for (i = 0; i < M; i++) {
        matriz[arestas[i].u][arestas[i].v] = arestas[i].w;
        matriz[arestas[i].v][arestas[i].u] = arestas[i].w;
    }
}

static void imprimirCaminho(int v) {
    if (pred[v] == -1) { printf("%d", v); return; }
    imprimirCaminho(pred[v]);
    printf(" -> %d", v);
}

/* DFS recursiva: aprofunda o maximo possivel antes de voltar (backtracking).
   Os vizinhos sao examinados em ordem crescente (lendo a matriz). */
static void dfs(int u, int profundidade) {
    int i;
    visitado[u] = 1;
    desc[u] = ++tempo;
    ordem[qtd++] = u;
    printf("  %*sentra no %d (profundidade %d, tempo %d)\n",
           profundidade * 2, "", u, profundidade, desc[u]);

    for (i = 0; i < N; i++) {
        if (matriz[u][i] != 0 && !visitado[i]) {
            pred[i] = u;
            dfs(i, profundidade + 1);
        }
    }

    fim[u] = ++tempo;
    printf("  %*ssai do %d (tempo %d)%s\n", profundidade * 2, "", u, fim[u],
           pred[u] != -1 ? "   <- volta para o pai" : "");
}

int main(void) {
    int i, origem = 8;

    construirMatriz();
    for (i = 0; i < N; i++) { visitado[i] = 0; pred[i] = -1; }

    printf("=== BUSCA EM PROFUNDIDADE (DFS) - origem = %d ===\n", origem);
    dfs(origem, 0);

    printf("\nOrdem de visita: ");
    for (i = 0; i < qtd; i++) printf("%d%s", ordem[i], i < qtd - 1 ? " -> " : "\n");

    printf("\nTempos e caminhos na arvore da DFS:\n");
    for (i = 0; i < N; i++) {
        printf("  no %d: descoberta %2d, termino %2d   caminho: ", i, desc[i], fim[i]);
        imprimirCaminho(i);
        printf("\n");
    }
    printf("\n");

    system("pause");
    return 0;
}