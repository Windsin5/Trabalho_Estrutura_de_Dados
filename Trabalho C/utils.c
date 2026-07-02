/* =========================================================
   utils.c  –  utilitários gerais (horário, menu, atendimento)
   ========================================================= */

#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "cores.h"

/* ---- contadores de senha ---- */
static int proximaSenhaNormal       = 1001;
static int proximaSenhaPreferencial = 101;

/* ---- horário ---- */
void obterHorario(char *buf, int tam) {
    time_t     t       = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, tam, "%H:%M:%S", tm_info);
}

/* ---- criação de pessoas ---- */
Pessoa criarPessoaNormal(void) {
    Pessoa p;
    p.senha = proximaSenhaNormal++;
    p.tipo  = 'N';
    obterHorario(p.horario, sizeof(p.horario));
    return p;
}

Pessoa criarPessoaPreferencial(void) {
    Pessoa p;
    p.senha = proximaSenhaPreferencial++;
    p.tipo  = 'P';
    obterHorario(p.horario, sizeof(p.horario));
    return p;
}

/* ---- exibição de atendimento ---- */
void exibirCabecalho(void) {
    printf(COR_LARANJA
           "\n  %-10s %-12s %-20s  %s\n"
           "  %s\n" COR_RESET,
           "Senha", "Tipo", "Horário", "Guichê",
           "____________________________________________________");
}

void exibirAtendimento(const Pessoa *p, int guiche) {
    printf(COR_LARANJA
           "  %-10d %-12c %-20s  [Guichê %d]\n"
           COR_RESET,
           p->senha, p->tipo, p->horario, guiche);
}

/* ---- menu (violeta) ---- */
void exibirMenu(void) {
    printf(COR_VIOLETA COR_NEGRITO
           "\n____________________________________\n"
           "|    BANCO ÁGIL - SENHAS           |\n"
           "____________________________________\n"
           "|  1. Emitir senha NORMAL          |\n"
           "|  2. Emitir senha PREFERENCIAL    |\n"
           "|  3. Chamar próximas senhas       |\n"
           "|  4. Exibir filas                 |\n"
           "|  5. Buscar senha                 |\n"
           "|  6. Salvar filas em CSV          |\n"
           "|  0. Sair                         |\n"
           "____________________________________\n"
           COR_RESET);
    printf(COR_VIOLETA "  Opção: " COR_RESET);
}

/* ---- atendimento 2N : 1P (laranja) ---- */
void realizarAtendimento(FilaNormal *fn, FilaCircular *fp) {
    Pessoa p;
    int atendidos = 0;

    printf(COR_LARANJA COR_NEGRITO
           "\n________________________________________________________\n"
           "|             INICIANDO ATENDIMENTO                    |\n"
           "________________________________________________________\n"
           COR_RESET);
    exibirCabecalho();

    /*
      Ciclo: até 2 senhas normais, depois 1 preferencial.
      Se uma fila esvazia, continua pela outra.
    */
    while (!filaVaziaNormal(fn) || !filaVaziaCircular(fp)) {

        /* atende até 2 senhas normais */
        int chamadas_normais = 0;
        while (chamadas_normais < 2 && !filaVaziaNormal(fn)) {
            desenfileirarNormal(fn, &p);
            exibirAtendimento(&p, 1);
            chamadas_normais++;
            atendidos++;
        }

        /* atende 1 senha preferencial (se houver) */
        if (!filaVaziaCircular(fp)) {
            desenfileirarCircular(fp, &p);
            exibirAtendimento(&p, 2);
            atendidos++;
        }
    }

    printf(COR_LARANJA
           "  ----------------------------------------------------\n"
           "  Total atendido: %d pessoa(s)\n\n"
           COR_RESET, atendidos);
}
