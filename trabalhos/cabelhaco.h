#ifndef LISTA_TP_H
#define LISTA_TP_H

typedef struct ListaTorcedoresPrioridade ListaTP;

ListaTP* criaLista(void);
int insereNaLista(ListaTP* Lista, char categoria);
int RemoveDaLista(ListaTP* Lista, int senha);
void exibeLista(ListaTP* Lista);
void freeElementoDaLista(ListaTP* Lista);

#endif