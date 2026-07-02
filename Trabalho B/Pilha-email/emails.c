#include "emails.h"

Pilha *criarPilha(int capacidade) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    if (!p) return NULL;
    p->capacidade = capacidade;
    p->topo = -1;
    p->itens = (Email **) malloc(capacidade * sizeof(Email *));
    if (!p->itens) { free(p); return NULL; }
    return p;
}

void destruirPilha(Pilha *p) {
    if (!p) return;
    while (!pilhaVazia(p)) {
        Email *e = desempilhar(p);
        free(e);
    }
    free(p->itens);
    free(p);
}

int pilhaVazia(Pilha *p) {
    return (p->topo == -1);
}

int pilhaCheia(Pilha *p) {
    return (p->topo == p->capacidade - 1);
}

int empilhar(Pilha *p, Email *e) {
    if (pilhaCheia(p)) return 0;
    p->itens[++(p->topo)] = e;
    return 1;
}

Email *desempilhar(Pilha *p) {
    if (pilhaVazia(p)) return NULL;
    return p->itens[(p->topo)--];
}

Email *espiar(Pilha *p) {
    if (pilhaVazia(p)) return NULL;
    return p->itens[p->topo];
}

void listarEmails(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\n[i] Nao ha e-mails na Caixa de Entrada.\n");
        return;
    }
    printf("\n======= CAIXA DE ENTRADA (%d e-mail(s)) =======\n", p->topo + 1);
    /* Exibe do topo (mais recente) para a base (mais antigo) */
    for (int i = p->topo; i >= 0; i--) {
        printf("ID: %-4d | De: %-20.20s | Assunto: %-30.30s | Data: %s\n",
               p->itens[i]->id, p->itens[i]->remetente, p->itens[i]->assunto, p->itens[i]->data);
    }
    printf("================================================\n");
}

int marcarComoLido(Pilha *p, int id) {
    if (pilhaVazia(p)) {
        printf("\n[x] Erro: Caixa de entrada vazia.\n");
        return 0;
    }

    Pilha *aux = criarPilha(p->capacidade);
    int achou = 0;
    Email *alvo = NULL;

    /* Desempilha procurando o ID */
    while (!pilhaVazia(p)) {
        Email *e = desempilhar(p);
        if (e->id == id) {
            achou = 1;
            alvo = e;
            break; /* Remove o e-mail alvo do fluxo principal */
        }
        empilhar(aux, e);
    }

    /* Devolve os e-mails que estavam acima dele mantendo a ordem original */
    while (!pilhaVazia(aux)) {
        empilhar(p, desempilhar(aux));
    }
    destruirPilha(aux);

    if (achou && alvo) {
        printf("\n=========================================\n");
        printf("|         E-MAIL MARCADO COMO LIDO        |\n");
        printf("===========================================\n");
        printf("| ID        : %-28d |\n", alvo->id);
        printf("| De        : %-28.28s |\n", alvo->remetente);
        printf("| Assunto   : %-28.28s |\n", alvo->assunto);
        printf("| Data      : %-28s |\n", alvo->data);
        printf("===========================================\n");
        free(alvo);
        return 1;
    } else {
        printf("\n[x] Erro: E-mail com ID %d nao foi encontrado.\n", id);
        return 0;
    }
}

void salvarCSV(Pilha *p, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (!f) {
        printf("\n[x] Erro ao abrir arquivo para salvar.\n");
        return;
    }
    /* Salva da base para o topo para manter a ordem cronologica na releitura */
    for (int i = 0; i <= p->topo; i++) {
        fprintf(f, "%d;%s;%s;%s\n",
                p->itens[i]->id, p->itens[i]->remetente, p->itens[i]->assunto, p->itens[i]->data);
    }
    fclose(f);
    printf("\n[+] %d e-mail(s) salvos com sucesso em '%s'.\n", p->topo + 1, arquivo);
}

void carregarCSV(Pilha *p, const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        printf("\n[i] Nenhum arquivo de backup encontrado. Iniciando caixa vazia.\n");
        return;
    }

    while (!pilhaVazia(p)) {
        free(desempilhar(p));
    }

    char linha[600];
    int cont = 0;

    while (fgets(linha, sizeof(linha), f) && !pilhaCheia(p)) {
        /* Remove o \n do final da linha se existir */
        linha[strcspn(linha, "\n")] = '\0';

        char *token_id        = strtok(linha, ";");
        char *token_remetente = strtok(NULL, ";");
        char *token_assunto   = strtok(NULL, ";");
        char *token_data      = strtok(NULL, ";");

        if (token_id && token_remetente && token_assunto && token_data) {
            Email *e = criarEmail(atoi(token_id), token_remetente, token_assunto, token_data);
            if (e) {
                empilhar(p, e);
                cont++;
            }
        }
    }
    fclose(f);
    printf("\n[+] %d e-mail(s) carregados com sucesso de '%s'.\n", cont, arquivo);
}

Email *criarEmail(int id, const char *remetente, const char *assunto, const char *data) {
    Email *e = (Email *) malloc(sizeof(Email));
    if (!e) return NULL;
    e->id = id;
    strncpy(e->remetente, remetente, TAM_REMETENTE - 1);
    e->remetente[TAM_REMETENTE - 1] = '\0';
    strncpy(e->assunto, assunto, TAM_ASSUNTO - 1);
    e->assunto[TAM_ASSUNTO - 1] = '\0';
    strncpy(e->data, data, TAM_DATA - 1);
    e->data[TAM_DATA - 1] = '\0';
    return e;
}