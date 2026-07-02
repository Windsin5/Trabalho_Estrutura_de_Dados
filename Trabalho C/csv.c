/* =========================================================
   csv.c  –  persistência em arquivo CSV
   ========================================================= */

#include <stdio.h>
#include "csv.h"
#include "cores.h"

/* ---- escrita de uma linha CSV ---- */
static void escreverLinha(FILE *f, const Pessoa *p) {
    fprintf(f, "%d;%c;%s\n", p->senha, p->tipo, p->horario);
}

/* ---- salvar estado atual das filas ---- */
int csvSalvarFilas(const FilaNormal *fn, const FilaCircular *fp) {
    FILE *f = fopen(CSV_ARQUIVO, "w");
    if (!f) {
        printf(COR_VERMELHO
               "\n  Erro ao abrir/criar '%s'.\n" COR_RESET,
               CSV_ARQUIVO);
        return 0;
    }

    /* cabeçalho descritivo */
    fprintf(f, "senha;tipo;horario\n");

    /* percorre fila normal (encadeada simples) */
    const NoNormal *n = fn->inicio;
    while (n) {
        escreverLinha(f, &n->dados);
        n = n->prox;
    }

    /* percorre fila circular */
    if (!filaVaziaCircular(fp)) {
        const NoCircular *inicio = fp->fim->prox;
        const NoCircular *atual  = inicio;
        do {
            escreverLinha(f, &atual->dados);
            atual = atual->prox;
        } while (atual != inicio);
    }

    fclose(f);
    printf(COR_VERDE
           "\n  Filas salvas em '%s' (%d normal + %d preferencial).\n"
           COR_RESET,
           CSV_ARQUIVO, fn->tamanho, fp->tamanho);
    return 1;
}

/* quando se dá um adendo de um atendimento concluído */
int csvSalvarAtendimento(const Pessoa *p, const char *arquivo) {
    FILE *f = fopen(arquivo, "a");
    if (!f) return 0;
    escreverLinha(f, p);
    fclose(f);
    return 1;
}
