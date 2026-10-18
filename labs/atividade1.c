//Complexidade: fibonacci iterativa x recursiva
// fazer uma funcao fibonacci iterativa
// e outra recursiva

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
int fibonacci_int(int n)
{
    int anterior = 0, atual = 1, proximo;
    if (n == 1) return 0;
    if (n == 2) return 1;
    for (int i = 2; i <= n - 1; i++)
    {
        proximo = atual + anterior;
        anterior = atual;
        atual = proximo;
    }
    return atual;
}
int fibonacci_recur(int n)
{
    if (n == 1)
    {
        return 0;
    }
    else
    {
        if (n == 2)
            return 1;
        else
            return fibonacci_recur(n - 1) + fibonacci_recur(n - 2);
    }
}
int main(void)
{
    int valores[] = { 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 35, 40, 45, 46, 47};
    int qtd = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < qtd; i++)
    {
        int n = valores[i];
        struct timeval inicio_it, fim_it;
        gettimeofday(&inicio_it, NULL);
        int resultado_int = fibonacci_int(n);
        gettimeofday(&fim_it, NULL);
        double tempo_it = (fim_it.tv_sec - inicio_it.tv_sec) +
                           (fim_it.tv_usec - inicio_it.tv_usec) / 1000000.0;
        struct timeval inicio_rec, fim_rec;
        gettimeofday(&inicio_rec, NULL);
        int resultado_recur = fibonacci_recur(n);
        gettimeofday(&fim_rec, NULL);
        double tempo_rec = (fim_rec.tv_sec - inicio_rec.tv_sec) +
                            (fim_rec.tv_usec - inicio_rec.tv_usec) / 1000000.0;
        printf("n = %d | iterativo=%d (%.6f s) | recursivo=%d (%.6f s)\n",
               n, resultado_int, tempo_it, resultado_recur, tempo_rec);
    }
    return 0;
}
