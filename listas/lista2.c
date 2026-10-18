#include <stdio.h>
#include <string.h>

typedef struct no{
    int valor;
    int posicao;
    struct no *dir;
    struct no *esq;
}noarv;
//5) Escreva em C uma função que recebe como parâmetro o endereço do nó raiz de uma ABB e
//um número inteiro. A função deve retornar o endereço do nó da chave imediatamente
//maior do que a chave dada. Se a chave não pertencer à árvore a função deve retornar NULL.

noarv*sucessor(noarv *raiz,int valor){
    noarv*atual= raiz;
    noarv*encontrado=NULL;
    noarv*sucessor= NULL;
    while(atual != NULL){
        if(valor< atual->valor){
           sucessor = atual; 
           atual = atual->esq;
        }else if(valor>atual->valor){
            atual = atual->dir;
        }else{
            encontrado = atual;
            break;
        }
    }
    if(encontrado == NULL){
        return NULL;
    }
    if(encontrado->dir != NULL){
        noarv*aux = encontrado->dir;
        while(aux->esq != NULL && aux->esq>valor){
            aux = aux->esq;
        }
        return aux;
    }
};

//6))
//a)
// Função auxiliar recursiva
void atribuir_posicoes_aux(noarv *raiz, int *contador) {
    if (raiz == NULL) {
        return;
    }
    atribuir_posicoes_aux(raiz->esq, contador);

    raiz->posicao= *contador;
    (*contador)++;

    atribuir_posicoes_aux(raiz->dir, contador);
}

// Função principal solicitada no item (a)
void atribuir_posicoes(noarv *raiz) {
    int contador = 1;
    atribuir_posicoes_aux(raiz, &contador);
}
//b)
noarv* buscar_por_posicao(noarv *raiz, int k) {
    if (raiz == NULL) {
        return NULL; // Posição k não encontrada
    }

    if (k == raiz->posicao) {
        return raiz; // Nó encontrado
    } 
    else if (k < raiz->posicao) {
        return buscar_por_posicao(raiz->esq, k); // Busca na subárvore esquerda
    } 
    else {
        return buscar_por_posicao(raiz->dir, k);  // Busca na subárvore direita
    }
}





//8) algoritmo de insercao em ABB
noarv*inserir_versao1(noarv*raiz,int num){
    if(raiz == NULL){
        noarv *aux = malloc(sizeof(noarv));
        aux->valor = num;
        aux->esq= NULL;
        aux->dir = NULL;
        return aux;
    }
    else{
        if(num<raiz->valor){
            raiz->esq = inserir_versao1(raiz->esq,num);
        }
        else{
            raiz->dir = inserir_versao1(raiz->dir,num);
        }
        return raiz;
    }
}
//inserir sem retorno
void inserir_sem_retorno(noarv**raiz,int num){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(noarv));
        (*raiz)->valor = num;
        (*raiz)->esq = NULL;
        (*raiz)->dir= NULL;
    }
    else{
        if(num<(*raiz)->valor){
            inserir_sem_retorno(&((*raiz)->esq),num);
        }
        else{
            inserir_sem_retorno(&((*raiz)->dir),num);
        }
            
        
    }
}
//9)Escrever o algoritmo de remoção em ABB.
noarv* menor_no(noarv*raiz) {
    noarv *atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}
noarv* remover(noarv *raiz, int chave) {
    if (raiz == NULL) {
        return NULL;
    }

    if (chave < raiz->valor) {
        raiz->esq = remover(raiz->esq, chave);
    } 
    else if (chave > raiz->valor) {
        raiz->dir= remover(raiz->dir, chave);
    } 
    else {
        
        if (raiz->esq == NULL) {
            noarv *temp = raiz->dir;
            free(raiz);
            return temp; 
        } 
        else if (raiz->dir == NULL) {
            noarv *temp = raiz->esq;
            free(raiz);
            return temp; 
        }

        noarv *temp = menor_no(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir= remover(raiz->dir, temp->valor);
    }
    return raiz;
}
// funcao de buscar
noarv* buscar_versao2(noarv*raiz, int num){
    while(raiz){
        if(num<raiz->valor){
            raiz = raiz->esq;
        }
        else if(num>raiz->valor){
            raiz = raiz->valor;
        }
        else{
            return raiz;
        }
    }
    return NULL;
}

noarv* buscar_retorno(noarv*raiz, int num){
    if(raiz){
        if(num == raiz->valor){
            return raiz;
        }
        else if(num <raiz->valor){
            buscar_retorno(raiz->esq,num);
        }
        else{
            buscar_retorno(raiz->dir,num);
        } 
    }
    return NULL;
}
//10) funcao de imprimir arvore
void imprimir_versao_1(noarv* raiz){
    if(raiz){
        printf("%d",raiz->valor);
        imprimir_versao_1(raiz->esq);
        imprimir_versao_1(raiz->dir);
    }
}
void imprimir_versao_2(noarv* raiz){
    if(raiz){
        imprimir_versao_2(raiz->esq);
        printf("%d",raiz->valor); 
        imprimir_versao_2(raiz->dir);
    }
}
//11) funcao de calcular altura
int altura(noarv*raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        int esq = altura(raiz->esq);
        int dir = altura(raiz->dir);
        if(esq>dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    }
}
