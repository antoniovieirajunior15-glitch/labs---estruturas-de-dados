#include <stdio.h>
#include <stdlib.h>


#define N 9         
#define M 14        
typedef struct { int u, v, w; } Aresta;

static Aresta arestas[M] = {
    {0, 1, 4},  {0, 7, 8},  {1, 2, 8},  {1, 7, 11},
    {2, 3, 7},  {2, 8, 2},  {2, 5, 4},  {3, 4, 9},
    {3, 5, 14}, {4, 5, 10}, {5, 6, 2},  {6, 7, 1},
    {6, 8, 6},  {7, 8, 7}
};

static int matriz[N][N];

static void construirMatriz(void) {
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) matriz[i][j] = 0;  
    for (i = 0; i < M; i++) {
        matriz[arestas[i].u][arestas[i].v] = arestas[i].w;
        matriz[arestas[i].v][arestas[i].u] = arestas[i].w;
    }
}

static void imprimirCaminho(int pred[], int v) {
    if (pred[v] == -1) { printf("%d", v); return; }
    imprimirCaminho(pred, pred[v]);
    printf(" -> %d", v);
}

static void bfs(int origem) {
    int fila[N], ini = 0, fim = 0;
    int visitado[N], nivel[N], pred[N];
    int i, passo = 0;

    for (i = 0; i < N; i++) { visitado[i] = 0; nivel[i] = -1; pred[i] = -1; }

    visitado[origem] = 1;
    nivel[origem] = 0;
    fila[fim++] = origem;

    printf("=== BUSCA EM AMPLITUDE (BFS) - origem = %d ===\n", origem);
    while (ini < fim) {
        int u = fila[ini++];                    
        printf("  Passo %d: visita no %d (nivel %d)\n", ++passo, u, nivel[u]);
        for (i = 0; i < N; i++) {
            if (matriz[u][i] != 0 && !visitado[i]) {
                visitado[i] = 1;
                nivel[i] = nivel[u] + 1;
                pred[i] = u;
                fila[fim++] = i;                 
                printf("     descobre %d (via %d)\n", i, u);
            }
        }
    }

    printf("\nOrdem de visita: ");
    for (i = 0; i < N; i++) printf("%d%s", fila[i], i < N - 1 ? " -> " : "\n");

    printf("\nNiveis e caminhos (menor numero de arestas):\n");
    for (i = 0; i < N; i++) {
        printf("  no %d: nivel %d   caminho: ", i, nivel[i]);
        imprimirCaminho(pred, i);
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    construirMatriz();
    bfs(8);

    system("pause");
    return 0;
}
