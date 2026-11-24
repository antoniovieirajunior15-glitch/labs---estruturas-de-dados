#include <stdio.h>
#include <stdlib.h>

struct set {
    int n;              
    unsigned char* v;   
};
typedef struct set Set;

typedef Set BitVector;
// exercicio 1
BitVector* bvCompl(BitVector* a) {
    int i;
    BitVector* c = (BitVector*) malloc(sizeof(BitVector));
    if (c == NULL) return NULL;

    c->n = a->n;
    c->v = (unsigned char*) malloc(a->n * sizeof(unsigned char));
    if (c->v == NULL) {
        free(c);
        return NULL;
    }

    for (i = 0; i < a->n; i++)
        c->v[i] = (unsigned char) ~(a->v[i]);

    return c;
}
//exercicio 2
int contem(Set* A, Set* B) {
    int i;
    int menor = (A->n < B->n) ? A->n : B->n;

    for (i = 0; i < menor; i++) {
        if ((A->v[i] & B->v[i]) != B->v[i])
            return 0;
    }

    for (i = menor; i < B->n; i++) {
        if (B->v[i] != 0)
            return 0;
    }

    return 1;
}

int main(void) {
    unsigned char va[] = {0xFF, 0x0F};
    unsigned char vb[] = {0x0F, 0x03, 0x00};
    unsigned char vc[] = {0x0F, 0x03, 0x01};

    Set A = {2, va};
    Set B = {3, vb};
    Set C = {3, vc};

    printf("A contem B? %d\n", contem(&A, &B));
    printf("A contem C? %d\n", contem(&A, &C));

    BitVector* comp = bvCompl(&A);
    printf("compl: %02X %02X\n", comp->v[0], comp->v[1]);
    free(comp->v);
    free(comp);
    return 0;
}