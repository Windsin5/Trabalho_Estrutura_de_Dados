#ifndef EMAILS_H
#define EMAILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===== CONFIGURAÇÕES ===== */
#define MAX_EMAILS     100
#define TAM_REMETENTE  100
#define TAM_ASSUNTO    200
#define TAM_DATA       20
#define CSV_FILE       "emails.csv"

/* ===== ESTRUTURA DO E-MAIL ===== */
typedef struct {
    int  id;
    char remetente[TAM_REMETENTE];
    char assunto[TAM_ASSUNTO];
    char data[TAM_DATA];
} Email;

/* ===== ESTRUTURA DA PILHA ===== */
typedef struct {
    Email **itens;   /* vetor de ponteiros (alocação dinâmica) */
    int    topo;
    int    capacidade;
} Pilha;

/* ===== PROTÓTIPOS ===== */
Pilha *criarPilha(int capacidade);
void   destruirPilha(Pilha *p);
int    pilhaVazia(Pilha *p);
int    pilhaCheia(Pilha *p);
int    empilhar(Pilha *p, Email *e);
Email *desempilhar(Pilha *p);
Email *espiar(Pilha *p);
void   listarEmails(Pilha *p);
int    marcarComoLido(Pilha *p, int id);
void   salvarCSV(Pilha *p, const char *arquivo);
void   carregarCSV(Pilha *p, const char *arquivo);
Email *criarEmail(int id, const char *remetente, const char *assunto, const char *data);

#endif