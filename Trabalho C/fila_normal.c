/* =========================================================
   fila_normal.c  –  fila NORMAL (lista encadeada simples)
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include "fila_normal.h"
#include "cores.h"

void inicializarFilaNormal(FilaNormal *fila) {
    fila->inicio  = NULL;
    fila->fim     = NULL;
    fila->tamanho = 0;
}

int filaVaziaNormal(const FilaNormal *fila) {
    return fila->tamanho == 0;
}

/* Enfileira pelo fim (FIFO). */
int enfileirarNormal(FilaNormal *fila, Pessoa p) {
    NoNormal *novo = (NoNormal *)malloc(sizeof(NoNormal));
    if (!novo) {
        fprintf(stderr, COR_VERMELHO
                "Erro: memória insuficiente!\n" COR_RESET);
        return 0;
    }
    novo->dados = p;
    novo->prox  = NULL;

    if (filaVaziaNormal(fila)) {
        fila->inicio = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
    fila->tamanho++;
    return 1;
}

/* Desenfileira do início (FIFO). */
int desenfileirarNormal(FilaNormal *fila, Pessoa *dest) {
    if (filaVaziaNormal(fila)) return 0;

    NoNormal *tmp = fila->inicio;
    *dest         = tmp->dados;
    fila->inicio  = tmp->prox;
    if (!fila->inicio) fila->fim = NULL;
    free(tmp);
    fila->tamanho--;
    return 1;
}

void liberarFilaNormal(FilaNormal *fila) {
    Pessoa p;
    while (desenfileirarNormal(fila, &p));
}

/* Busca por senha; retorna ponteiro para o nó ou NULL. */
NoNormal *buscarNormal(const FilaNormal *fila, int senha) {
    NoNormal *atual = fila->inicio;
    while (atual) {
        if (atual->dados.senha == senha) return atual;
        atual = atual->prox;
    }
    return NULL;
}

/* Exibe a fila com cor amarela. */
void exibirFilaNormal(const FilaNormal *fila) {
    printf(COR_AMARELO COR_NEGRITO
           "\n  Fila Normal (%d pessoa(s) aguardando):\n"
           COR_RESET, fila->tamanho);

    if (filaVaziaNormal(fila)) {
        printf(COR_AMARELO "    [vazia]\n" COR_RESET);
        return;
    }

    NoNormal *atual = fila->inicio;
    int pos = 1;
    while (atual) {
        printf(COR_AMARELO "    %d. Senha %d | %s\n" COR_RESET,
               pos++, atual->dados.senha, atual->dados.horario);
        atual = atual->prox;
    }
}
