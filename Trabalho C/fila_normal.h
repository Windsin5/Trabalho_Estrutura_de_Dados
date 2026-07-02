#ifndef FILA_NORMAL_H
#define FILA_NORMAL_H

/* =========================================================
   fila_normal.h  –  fila NORMAL (lista encadeada simples)
   ========================================================= */

#include "tipos.h"

typedef struct NoNormal {
    Pessoa           dados;
    struct NoNormal *prox;
} NoNormal;

typedef struct {
    NoNormal *inicio;
    NoNormal *fim;
    int       tamanho;
} FilaNormal;

void inicializarFilaNormal  (FilaNormal *fila);
int  filaVaziaNormal        (const FilaNormal *fila);
int  enfileirarNormal       (FilaNormal *fila, Pessoa p);
int  desenfileirarNormal    (FilaNormal *fila, Pessoa *dest);
void liberarFilaNormal      (FilaNormal *fila);
void exibirFilaNormal       (const FilaNormal *fila);

/* busca por senha; retorna ponteiro para o nó ou NULL */
NoNormal *buscarNormal      (const FilaNormal *fila, int senha);

#endif /* FILA_NORMAL_H */
