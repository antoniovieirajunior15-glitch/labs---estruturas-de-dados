#include <stdio.h>
#include <stdlib.h>

#define MAX 4
#define MIN 2

typedef struct no t_no;
struct no
{
    int ndesc;           
    int chave[MAX];      
    t_no *ramo[MAX + 1];
};

t_no *cria_no(int n, int c0, int c1, int c2, int c3)
{
    int v[4] = {c0, c1, c2, c3};
    int i;
    t_no *p = (t_no *) malloc(sizeof(t_no));
    if (p == NULL) { printf("Sem memoria\n"); exit(1); }
    p->ndesc = n + 1;
    for (i = 0; i < MAX; i++)
        p->chave[i] = (i < n) ? v[i] : 0;
    for (i = 0; i <= MAX; i++)
        p->ramo[i] = NULL;
    return p;
}

/* Questão 1: monta a árvore pedida (folhas primeiro, depois interiores) */
t_no *cria_arvore(void)
{

    t_no *f1 = cria_no(2, 10, 40, 0, 0);
    t_no *f2 = cria_no(2, 60, 70, 0, 0);
    t_no *f3 = cria_no(2, 80, 90, 0, 0);
    t_no *f4 = cria_no(2, 110, 115, 0, 0);
    t_no *f5 = cria_no(4, 130, 135, 140, 170);
    t_no *f6 = cria_no(4, 220, 230, 240, 250);


    t_no *n1 = cria_no(2, 50, 75, 0, 0);
    t_no *n2 = cria_no(2, 120, 200, 0, 0);
    t_no *raiz = cria_no(1, 100, 0, 0, 0);

    n1->ramo[0] = f1; n1->ramo[1] = f2; n1->ramo[2] = f3;
    n2->ramo[0] = f4; n2->ramo[1] = f5; n2->ramo[2] = f6;
    raiz->ramo[0] = n1; raiz->ramo[1] = n2;

    return raiz;
}

/* Questão 2: imprime em ordem simétrica as chaves x com lim_inf < x < lim_sup */
void intervalo(t_no *arv, int lim_inf, int lim_sup)
{
    int i;
    if (arv == NULL) return;

    for (i = 0; i < arv->ndesc - 1; i++)
    {
        if (arv->chave[i] > lim_inf)
            intervalo(arv->ramo[i], lim_inf, lim_sup);

        if (arv->chave[i] > lim_inf && arv->chave[i] < lim_sup)
            printf("%d ", arv->chave[i]);

        if (arv->chave[i] >= lim_sup)  
            return;
    }
    intervalo(arv->ramo[arv->ndesc - 1], lim_inf, lim_sup);
}

/* Busca de uma chave na árvore B (retorna 1 se achou, 0 caso contrário) */
int busca(t_no *arv, int x)
{
    int i;
    while (arv != NULL)
    {
        for (i = 0; i < arv->ndesc - 1 && x > arv->chave[i]; i++)
            ;
        if (i < arv->ndesc - 1 && x == arv->chave[i])
            return 1;
        arv = arv->ramo[i];
    }
    return 0;
}

void libera(t_no *arv)
{
    int i;
    if (arv == NULL) return;
    for (i = 0; i < arv->ndesc; i++)
        libera(arv->ramo[i]);
    free(arv);
}

int main(void)
{
    t_no *arv = cria_arvore();

    /* a) busca da chave 230 */
    if (busca(arv, 230))
        printf("a) A chave 230 ESTA na arvore.\n");
    else
        printf("a) A chave 230 NAO esta na arvore.\n");

    /* b) chaves em [50,170]: como intervalo() é estrito (lim_inf < x < lim_sup),
          usamos 49 e 171 para incluir 50 e 170 */
    printf("b) Chaves em [50,170]: ");
    intervalo(arv, 49, 171);
    printf("\n");

    libera(arv);
    return 0;
}