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

    /* parte em que os dois vetores têm bytes */
    for (i = 0; i < menor; i++) {
        if ((A->v[i] & B->v[i]) != B->v[i])
            return 0;
    }

    /* se B é maior, os bytes restantes de B devem ser 0 */
    for (i = menor; i < B->n; i++) {
        if (B->v[i] != 0)
            return 0;
    }

    return 1;
}
