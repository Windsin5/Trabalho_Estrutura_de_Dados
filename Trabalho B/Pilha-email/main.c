#include <stdio.h>
#include <stdlib.h>
#include "emails.h"

int main() {
    Pilha *inbox = criarPilha(MAX_EMAILS);
    if (!inbox) {
        printf("[x] Erro fatal: Nao foi possivel inicializar a memoria da Pilha.\n");
        return 1;
    }

    carregarCSV(inbox, CSV_FILE);

    int opcao = -1;
    int proximoId = 1;

    if (!pilhaVazia(inbox)) {
        int maxId = 0;
        for (int i = 0; i <= inbox->topo; i++) {
            if (inbox->itens[i]->id > maxId) maxId = inbox->itens[i]->id;
        }
        proximoId = maxId + 1;
    }

    while (opcao != 0) {
        printf("\n================ MENU CONSOLE INBOX ================\n");
        printf("1 - Receber Novo E-mail (Empilhar)\n");
        printf("2 - Ler E-mail Mais Recente (Desempilhar)\n");
        printf("3 - Espiar E-mail Mais Recente (Topo)\n");
        printf("4 - Listar Todos os E-mails da Caixa\n");
        printf("5 - Marcar E-mail Especifico como Lido\n");
        printf("6 - Forcar Salvar Backup (CSV)\n");
        printf("7 - Forcar Carregar Backup (CSV)\n");
        printf("0 - Sair e Salvar Automaticamente\n");
        printf("====================================================\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("\n[x] Entrada invalida. Digite um numero inteiro.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            continue;
        }
        getchar(); 

        switch (opcao) {
            case 1: { /* Receber */
                if (pilhaCheia(inbox)) {
                    printf("\n[x] Erro: Caixa de entrada cheia (%d e-mails).\n", MAX_EMAILS);
                    break;
                }
                char remetente[TAM_REMETENTE];
                char assunto[TAM_ASSUNTO];
                char dataStr[TAM_DATA];

                printf("Digite o Remetente : ");
                fgets(remetente, sizeof(remetente), stdin);
                remetente[strcspn(remetente, "\n")] = '\0';

                printf("Digite o Assunto   : ");
                fgets(assunto, sizeof(assunto), stdin);
                assunto[strcspn(assunto, "\n")] = '\0';

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                snprintf(dataStr, sizeof(dataStr), "%02d/%02d/%d %02d:%02d",
                         tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

                Email *novo = criarEmail(proximoId++, remetente, assunto, dataStr);
                if (novo && empilhar(inbox, novo)) {
                    printf("\n[+] Novo e-mail recebido com sucesso! ID gerado: %d\n", novo->id);
                } else {
                    printf("\n[x] Erro inesperado ao alocar ou empilhar e-mail.\n");
                    if (novo) free(novo);
                }
                break;
            }

            case 2: { /* Ler recente / Desempilhar */
                Email *e = desempilhar(inbox);
                if (!e) {
                    printf("\n[i] Nao ha e-mails nao lidos.\n");
                } else {
                    printf("\n=========================================\n");
                    printf("|            LENDO E-MAIL RECENTE         |\n");
                    printf("===========================================\n");
                    printf("| ID        : %-28d |\n", e->id);
                    printf("| De        : %-28.28s |\n", e->remetente);
                    printf("| Assunto   : %-28.28s |\n", e->assunto);
                    printf("| Data      : %-28s |\n", e->data);
                    printf("===========================================\n");
                    free(e);
                }
                break;
            }

            case 3: { /* Espiar topo */
                Email *e = espiar(inbox);
                if (!e) {
                    printf("\n[i] Caixa vazia.\n");
                } else {
                    printf("\n[Topo] ID %d | De: %s | Assunto: %s | Data: %s\n",
                           e->id, e->remetente, e->assunto, e->data);
                }
                break;
            }

            case 4:
                listarEmails(inbox);
                break;

            case 5: { /* Marcar específico como lido */
                int id;
                printf("Digite o ID do e-mail a marcar como lido: ");
                if (scanf("%d", &id) == 1) {
                    marcarComoLido(inbox, id);
                }
                getchar(); 
                break;
            }

            case 6:
                salvarCSV(inbox, CSV_FILE);
                break;

            case 7:
                carregarCSV(inbox, CSV_FILE);
                if (!pilhaVazia(inbox)) {
                    int maxId = 0;
                    for (int i = 0; i <= inbox->topo; i++) {
                        if (inbox->itens[i]->id > maxId) maxId = inbox->itens[i]->id;
                    }
                    proximoId = maxId + 1;
                }
                break;

            case 0:
                salvarCSV(inbox, CSV_FILE);
                break;

            default:
                printf("\n[x] Opcao invalida. Tente novamente.\n");
        }
    }

    destruirPilha(inbox);
    return 0;
}