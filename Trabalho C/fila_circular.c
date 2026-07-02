/* =========================================================
   fila_circular.c  –  fila PREFERENCIAL (lista circular simples)
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "fila_circular.h"
#include "cores.h"

void inicializarFilaCircular(FilaCircular *fila) {
    fila->fim     = NULL;
    fila->tamanho = 0;
}

int filaVaziaCircular(const FilaCircular *fila) {
    return fila->tamanho == 0;
}

/* Enfileira pelo fim; o nó antigo "fim" passa a apontar para o novo. */
int enfileirarCircular(FilaCircular *fila, Pessoa p) {
    NoCircular *novo = (NoCircular *)malloc(sizeof(NoCircular));
    if (!novo) {
        fprintf(stderr, COR_VERMELHO
                "Erro: memória insuficiente!\n" COR_RESET);
        return 0;
    }
    novo->dados = p;

    if (filaVaziaCircular(fila)) {
        novo->prox = novo;          /* aponta pra si mesmo */
    } else {
        novo->prox      = fila->fim->prox;   /* novo->prox = antigo início */
        fila->fim->prox = novo;
    }
    fila->fim = novo;               /* fecha o círculo */
    fila->tamanho++;
    return 1;
}

/* Desenfileira do início (fim->prox). */
int desenfileirarCircular(FilaCircular *fila, Pessoa *dest) {
    if (filaVaziaCircular(fila)) return 0;

    NoCircular *inicio = fila->fim->prox;
    *dest = inicio->dados;

    if (fila->tamanho == 1) {
        fila->fim = NULL;
    } else {
        fila->fim->prox = inicio->prox;
    }
    free(inicio);
    fila->tamanho--;
    return 1;
}

void liberarFilaCircular(FilaCircular *fila) {
    Pessoa p;
    while (desenfileirarCircular(fila, &p));
}

/* Busca por senha; retorna ponteiro para o nó ou NULL. */
NoCircular *buscarCircular(const FilaCircular *fila, int senha) {
    if (filaVaziaCircular(fila)) return NULL;

    NoCircular *inicio = fila->fim->prox;
    NoCircular *atual  = inicio;
    do {
        if (atual->dados.senha == senha) return atual;
        atual = atual->prox;
    } while (atual != inicio);

    return NULL;
}

/* Exibe a fila com cor azul. */
void exibirFilaCircular(const FilaCircular *fila) {
    printf(COR_AZUL COR_NEGRITO
           "\n  Fila Preferencial (%d pessoa(s) aguardando):\n"
           COR_RESET, fila->tamanho);

    if (filaVaziaCircular(fila)) {
        printf(COR_AZUL "    [vazia]\n" COR_RESET);
        return;
    }

    NoCircular *inicio = fila->fim->prox;
    NoCircular *atual  = inicio;
    int pos = 1;
    do {
        printf(COR_AZUL "    %d. Senha %d | %s\n" COR_RESET,
               pos++, atual->dados.senha, atual->dados.horario);
        atual = atual->prox;
    } while (atual != inicio);
}
