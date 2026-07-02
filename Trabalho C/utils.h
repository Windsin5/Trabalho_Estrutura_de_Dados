#ifndef UTILS_H
#define UTILS_H

/* =========================================================
   utils.h  –  utilitários gerais (horário, menu, atendimento)
   ========================================================= */

#include "tipos.h"
#include "fila_normal.h"
#include "fila_circular.h"

/* Preenche buf com o horário atual no formato HH:MM:SS. */
void   obterHorario         (char *buf, int tam);

/* Construtores de Pessoa com senha auto-incrementada. */
Pessoa criarPessoaNormal    (void);
Pessoa criarPessoaPreferencial(void);

/* Exibição de uma linha de atendimento. */
void   exibirAtendimento    (const Pessoa *p, int guiche);
void   exibirCabecalho      (void);

/* Menu principal (cor violeta). */
void   exibirMenu           (void);

/* Lógica de atendimento 2N:1P (cor laranja). */
void   realizarAtendimento  (FilaNormal *fn, FilaCircular *fp);

#endif /* UTILS_H */
