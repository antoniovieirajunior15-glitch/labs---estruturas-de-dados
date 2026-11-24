#include <stdio.h>
#include <stdlib.h>

#define N 9          
#define M 14        
#define INF 1000000

typedef struct { int u, v, w; } Aresta;

/* Arestas do grafo da figura */
static Aresta arestas[M] = {
    {0, 1, 4},  {0, 7, 8},  {1, 2, 8},  {1, 7, 11},
    {2, 3, 7},  {2, 8, 2},  {2, 5, 4},  {3, 4, 9},
    {3, 5, 14}, {4, 5, 10}, {5, 6, 2},  {6, 7, 1},
    {6, 8, 6},  {7, 8, 7}
};


typedef struct No {
    int dest, peso;
    struct No* prox;
} No;

static int  matriz[N][N];
static No* lista[N];

static void inserirLista(int u, int v, int w) {
    No* n = (No*)malloc(sizeof(No));
    if (!n) { printf("Erro de memoria\n"); exit(1); }
    n->dest = v; n->peso = w;
    n->prox = lista[u];
    lista[u] = n;
}

static void construirGrafo(void) {
    int i, j;
    for (i = 0; i < N; i++) {
        lista[i] = NULL;
        for (j = 0; j < N; j++) matriz[i][j] = 0;   /* 0 = sem aresta */
    }
    for (i = 0; i < M; i++) {
        int u = arestas[i].u, v = arestas[i].v, w = arestas[i].w;
        matriz[u][v] = w;
        matriz[v][u] = w;
        inserirLista(u, v, w);
        inserirLista(v, u, w);
    }
}

static void imprimirMatriz(void) {
    int i, j;
    printf("=== MATRIZ DE ADJACENCIAS ===\n    ");
    for (j = 0; j < N; j++) printf("%3d ", j);
    printf("\n");
    for (i = 0; i < N; i++) {
        printf("%3d ", i);
        for (j = 0; j < N; j++) printf("%3d ", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

static void imprimirLista(void) {
    int i;
    printf("=== LISTA DE ADJACENCIAS (vizinho, peso) ===\n");
    for (i = 0; i < N; i++) {
        No* p;
        printf("%d: ", i);
        for (p = lista[i]; p != NULL; p = p->prox)
            printf("(%d,%d) -> ", p->dest, p->peso);
        printf("NULL\n");
    }
    printf("\n");
}

/* Kruskal (Árvore Geradora Mínima) com Union-Find  */
static int pai[N], rnk[N];

static int achar(int x) {
    if (pai[x] != x) pai[x] = achar(pai[x]);
    return pai[x];
}

static int unir(int a, int b) {
    a = achar(a); b = achar(b);
    if (a == b) return 0;
    if (rnk[a] < rnk[b]) { int t = a; a = b; b = t; }
    pai[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
    return 1;
}

static int cmpAresta(const void* a, const void* b) {
    return ((const Aresta*)a)->w - ((const Aresta*)b)->w;
}

static void kruskal(void) {
    Aresta ord[M];
    int i, escolhidas = 0, total = 0;

    for (i = 0; i < M; i++) ord[i] = arestas[i];
    qsort(ord, M, sizeof(Aresta), cmpAresta);
    for (i = 0; i < N; i++) { pai[i] = i; rnk[i] = 0; }

    printf("=== KRUSKAL ===\n");
    printf("Arestas ordenadas por peso:\n");
    for (i = 0; i < M; i++)
        printf("  (%d - %d) peso %d\n", ord[i].u, ord[i].v, ord[i].w);

    printf("\nPassos:\n");
    for (i = 0; i < M && escolhidas < N - 1; i++) {
        if (unir(ord[i].u, ord[i].v)) {
            printf("  ACEITA   (%d - %d) peso %d\n", ord[i].u, ord[i].v, ord[i].w);
            total += ord[i].w;
            escolhidas++;
        }
        else {
            printf("  REJEITA  (%d - %d) peso %d  (formaria ciclo)\n",
                ord[i].u, ord[i].v, ord[i].w);
        }
    }
    printf("\nPeso total da AGM: %d\n\n", total);
}

/* ---------- Dijkstra ---------- */
static void imprimirCaminho(int pred[], int v) {
    if (pred[v] == -1) { printf("%d", v); return; }
    imprimirCaminho(pred, pred[v]);
    printf(" -> %d", v);
}

static void dijkstra(int origem) {
    int dist[N], pred[N], visitado[N];
    int i, k;

    for (i = 0; i < N; i++) { dist[i] = INF; pred[i] = -1; visitado[i] = 0; }
    dist[origem] = 0;

    printf(" DIJKSTRA (origem = %d) \n", origem);
    for (k = 0; k < N; k++) {
        int u = -1;
        No* p;
        for (i = 0; i < N; i++)
            if (!visitado[i] && (u == -1 || dist[i] < dist[u])) u = i;
        if (u == -1 || dist[u] == INF) break;
        visitado[u] = 1;
        printf("  Visita no %d (dist = %d)\n", u, dist[u]);

        for (p = lista[u]; p != NULL; p = p->prox) {
            if (!visitado[p->dest] && dist[u] + p->peso < dist[p->dest]) {
                dist[p->dest] = dist[u] + p->peso;
                pred[p->dest] = u;
                printf("     relaxa %d: nova dist = %d (via %d)\n",
                    p->dest, dist[p->dest], u);
            }
        }
    }

    printf("\nMenores distancias a partir do no %d:\n", origem);
    for (i = 0; i < N; i++) {
        printf("  %d -> %d : %2d   caminho: ", origem, i, dist[i]);
        imprimirCaminho(pred, i);
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    construirGrafo();
    imprimirMatriz();
    imprimirLista();
    kruskal();
    dijkstra(8);

    system("pause");
    return 0;
}
