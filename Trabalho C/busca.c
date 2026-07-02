/* =========================================================
   busca.c  –  funções de busca nas filas
   ========================================================= */

#include <stdio.h>
#include <ctype.h>
#include "busca.h"
#include "cores.h"

/* ---- busca por número de senha ---- */
int buscarSenha(const FilaNormal *fn, const FilaCircular *fp, int senha) {
    int encontrado = 0;

    /* tenta na fila normal */
    const NoNormal *n = buscarNormal(fn, senha);
    if (n) {
        printf(COR_VERDE
               "\n  Senha %d encontrada na FILA NORMAL\n"
               "    Tipo: %c | Horário de emissão: %s\n"
               COR_RESET,
               n->dados.senha, n->dados.tipo, n->dados.horario);
        encontrado = 1;
    }

    /* tenta na fila preferencial */
    const NoCircular *c = buscarCircular(fp, senha);
    if (c) {
        printf(COR_VERDE
               "\n  Senha %d encontrada na FILA PREFERENCIAL\n"
               "    Tipo: %c | Horário de emissão: %s\n"
               COR_RESET,
               c->dados.senha, c->dados.tipo, c->dados.horario);
        encontrado = 1;
    }

    if (!encontrado) {
        printf(COR_VERMELHO
               "\n  Senha %d não encontrada em nenhuma fila.\n"
               COR_RESET, senha);
    }
    return encontrado;
}

/* ---- busca por tipo ('N' ou 'P') ---- */
int buscarPorTipo(const FilaNormal *fn, const FilaCircular *fp, char tipo) {
    int total = 0;
    tipo = (char)toupper((unsigned char)tipo);

    printf(COR_CIANO
           "\n  Pessoas do tipo '%c' aguardando:\n"
           COR_RESET, tipo);

    /* faz varredura na fila normal */
    const NoNormal *n = fn->inicio;
    int pos = 1;
    while (n) {
        if (n->dados.tipo == tipo) {
            printf(COR_CIANO
                   "    [Normal]       Senha %d | %s\n"
                   COR_RESET,
                   n->dados.senha, n->dados.horario);
            total++;
        }
        n = n->prox;
        pos++;
    }

    /* faz uma varredura na fila circular */
    if (!filaVaziaCircular(fp)) {
        const NoCircular *inicio = fp->fim->prox;
        const NoCircular *atual  = inicio;
        do {
            if (atual->dados.tipo == tipo) {
                printf(COR_CIANO
                       "    [Preferencial] Senha %d | %s\n"
                       COR_RESET,
                       atual->dados.senha, atual->dados.horario);
                total++;
            }
            atual = atual->prox;
        } while (atual != inicio);
    }

    if (total == 0) {
        printf(COR_VERMELHO
               "    Nenhuma pessoa do tipo '%c' na fila.\n"
               COR_RESET, tipo);
    } else {
        printf(COR_CIANO
               "  Total: %d pessoa(s).\n"
               COR_RESET, total);
    }
    return total;
}

/* ---- submenu interativo de busca ---- */
void menuBusca(const FilaNormal *fn, const FilaCircular *fp) {
    printf(COR_CIANO COR_NEGRITO
           "\n  ---- BUSCA ----\n"
           "  1. Buscar por número de senha\n"
           "  2. Listar todas as senhas normais (N)\n"
           "  3. Listar todas as senhas preferenciais (P)\n"
           "  Opção: "
           COR_RESET);

    int op;
    if (scanf("%d", &op) != 1) {
        while (getchar() != '\n');
        return;
    }

    switch (op) {
        case 1: {
            printf(COR_CIANO "  Informe o número da senha: " COR_RESET);
            int s;
            if (scanf("%d", &s) == 1) buscarSenha(fn, fp, s);
            break;
        }
        case 2:
            buscarPorTipo(fn, fp, 'N');
            break;
        case 3:
            buscarPorTipo(fn, fp, 'P');
            break;
        default:
            printf(COR_VERMELHO "  Opção inválida.\n" COR_RESET);
    }
}
