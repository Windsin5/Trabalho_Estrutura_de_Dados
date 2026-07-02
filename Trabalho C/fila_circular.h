#ifndef FILA_CIRCULAR_H
#define FILA_CIRCULAR_H

/* =========================================================
   fila_circular.h  –  fila PREFERENCIAL (lista circular simples)
   ========================================================= */

#include "tipos.h"

typedef struct NoCircular {
    Pessoa             dados;
    struct NoCircular *prox;
} NoCircular;

typedef struct {
    NoCircular *fim;    /* fim->prox == início (fecha o círculo) */
    int         tamanho;
} FilaCircular;

void inicializarFilaCircular (FilaCircular *fila);
int  filaVaziaCircular       (const FilaCircular *fila);
int  enfileirarCircular      (FilaCircular *fila, Pessoa p);
int  desenfileirarCircular   (FilaCircular *fila, Pessoa *dest);
void liberarFilaCircular     (FilaCircular *fila);
void exibirFilaCircular      (const FilaCircular *fila);

/* busca por senha; retorna ponteiro para o nó ou NULL */
NoCircular *buscarCircular   (const FilaCircular *fila, int senha);

#endif /* FILA_CIRCULAR_H */
