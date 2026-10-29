//   Tabela Hash com enderecamento aberto - chaves: CPF
//   Tamanho da tabela: 1201 (1o primo apos 1200 = 1000 chaves + 20% de folga)
//   Funcao hash: metodo da divisao  h1(k) = k mod M
//   Tratamento de colisoes: DUPLO HASH  h2(k) = 1 + (k mod (M-2))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define M        1201          
#define MAX_CHV  1000
#define REPS     300          
#define ARQUIVO_PADRAO "CPFs.txt"
 
typedef unsigned long long u64;
typedef enum { LIVRE, OCUPADO, REMOVIDO } Estado;
typedef enum { LINEAR, QUADRATICA, DUPLO } Estrategia;
 
typedef struct { u64 chave; Estado estado; } Celula;
typedef struct { Celula t[M]; int n; long long colisoes; } Tabela;
 
static const char *NOME[] = { "linear", "quadratica", "duplo" };
 

static int h1(u64 k) { return (int)(k % M); }
static int h2(u64 k) { return 1 + (int)(k % (M - 2)); }   

static int sonda(u64 k, long long i, Estrategia e) {
    switch (e) {
        case LINEAR:     return (int)((h1(k) + i) % M);
        case QUADRATICA: return (int)((h1(k) + i + i * i) % M);   
        default:         return (int)((h1(k) + i * h2(k)) % M);
    }
}
 

void iniciar(Tabela *T) { memset(T, 0, sizeof(Tabela)); }
 

int inserir(Tabela *T, u64 k, Estrategia e) {
    int primeiro_removido = -1;
    for (int i = 0; i < M; i++) {
        int idx = sonda(k, i, e);
        if (T->t[idx].estado == LIVRE) {
            if (primeiro_removido >= 0) idx = primeiro_removido;
            T->t[idx].chave = k; T->t[idx].estado = OCUPADO; T->n++;
            return 1;
        }
        if (T->t[idx].estado == REMOVIDO) {
            if (primeiro_removido < 0) primeiro_removido = idx;
        } else if (T->t[idx].chave == k) {
            return 0;                      
        } else {
            T->colisoes++;                  
        }
    }
    if (primeiro_removido >= 0) {
        T->t[primeiro_removido].chave = k;
        T->t[primeiro_removido].estado = OCUPADO; T->n++;
        return 1;
    }
    return -1;
}
 

int buscar(const Tabela *T, u64 k, Estrategia e) {
    for (int i = 0; i < M; i++) {
        int idx = sonda(k, i, e);
        if (T->t[idx].estado == LIVRE) return -1;
        if (T->t[idx].estado == OCUPADO && T->t[idx].chave == k) return idx;
    }
    return -1;
}
 
int remover(Tabela *T, u64 k, Estrategia e) {
    int idx = buscar(T, k, e);
    if (idx < 0) return 0;
    T->t[idx].estado = REMOVIDO; T->n--;
    return 1;
}
 
#ifdef _WIN32
#include <windows.h>
static double agora(void) {                        
    LARGE_INTEGER f, c;
    QueryPerformanceFrequency(&f); QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1e6 / (double)f.QuadPart;
}
#else
static double agora(void) {                         
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
}
#endif
 
int ler_arquivo(const char *nome, u64 *v, int max) {
    FILE *f = fopen(nome, "r");
    if (!f) { perror("abrir arquivo"); return 0; }
    char linha[128]; int n = 0;
    while (n < max && fgets(linha, sizeof linha, f)) {
        char d[16]; int c = 0;
        for (char *p = linha; *p && c < 15; p++) if (isdigit((unsigned char)*p)) d[c++] = *p;
        d[c] = 0;
        if (c == 11) v[n++] = strtoull(d, NULL, 10);
    }
    fclose(f);
    return n;
}
 
static Tabela T;
 
int main(int argc, char **argv) {
    static u64 chaves[MAX_CHV];
    const char *arquivo = (argc > 1) ? argv[1] : ARQUIVO_PADRAO;
    int total = ler_arquivo(arquivo, chaves, MAX_CHV);
    if (total == 0) {
        fprintf(stderr, "Nenhum CPF lido de \"%s\". Coloque o arquivo na mesma pasta do programa.\n", arquivo);
        return 1;
    }
    printf("Arquivo: %s\n", arquivo);
    printf("Chaves lidas: %d | Tamanho da tabela M = %d\n\n", total, M);
 

    FILE *fc = fopen("colisoes_acumuladas.csv", "w");
    fprintf(fc, "chaves,linear,quadratica,duplo\n");
    static long long acum[3][MAX_CHV + 1];
    for (int e = 0; e < 3; e++) {
        iniciar(&T);
        for (int i = 0; i < total; i++) { inserir(&T, chaves[i], e); acum[e][i + 1] = T.colisoes; }
    }
    for (int i = 1; i <= total; i++)
        fprintf(fc, "%d,%lld,%lld,%lld\n", i, acum[0][i], acum[1][i], acum[2][i]);
    fclose(fc);
 
   
    int tams[] = { 64, 128, 256, 512, 1000 };
    FILE *fr = fopen("resumo.csv", "w");
    fprintf(fr, "estrategia,chaves,colisoes,tempo_us\n");
    printf("%-11s %6s %10s %12s\n", "estrategia", "chaves", "colisoes", "tempo(us)");
    for (int e = 0; e < 3; e++)
        for (int s = 0; s < 5; s++) {
            int n = tams[s] < total ? tams[s] : total;
            double soma = 0; long long col = 0;
            for (int r = 0; r < REPS; r++) {
                iniciar(&T);
                double t0 = agora();
                for (int i = 0; i < n; i++) inserir(&T, chaves[i], e);
                soma += agora() - t0;
                col = T.colisoes;
            }
            double media = soma / REPS;
            printf("%-11s %6d %10lld %12.2f\n", NOME[e], n, col, media);
            fprintf(fr, "%s,%d,%lld,%.3f\n", NOME[e], n, col, media);
        }
    fclose(fr);
    iniciar(&T);
    for (int i = 0; i < total; i++) inserir(&T, chaves[i], DUPLO);
    u64 k = chaves[total / 2];
    printf("\nBusca %011llu: posicao %d\n", k, buscar(&T, k, DUPLO));
    printf("Remocao: %s\n", remover(&T, k, DUPLO) ? "ok" : "nao encontrada");
    printf("Busca apos remocao: %d (-1 = nao encontrada)\n", buscar(&T, k, DUPLO));
    printf("Reinsercao: %d | Fator de carga final: %.3f\n",
           inserir(&T, k, DUPLO), (double)T.n / M);
    return 0;
}