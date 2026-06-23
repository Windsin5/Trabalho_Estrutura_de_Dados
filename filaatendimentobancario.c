/*
  simulação de atendimento bancário
  - Fila Normal: lista encadeada simples 
  - Fila Preferencial: fila circular simples 
  regra: 2 senhas normais para cada 1 preferencial.
  se uma fila estiver vazia, atende pela outra.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
// a struct
 
typedef struct Pessoa {
    int   senha;
    char  tipo;        //N para normal e P para preferencial
    char  horario[20];
} Pessoa;
 
// nó da fila pra Normal (que é uma lista encadeada simples (percebe-se pelos ponteiros *inicio e *fim))
typedef struct NoNormal {
    Pessoa        dados;
    struct NoNormal *prox;
} NoNormal;
 
typedef struct {
    NoNormal *inicio;
    NoNormal *fim;
    int       tamanho;
} FilaNormal;
 
// nó da fila para Preferecial (é uma lista circular, percebe-se que só vai ter o ponteiro *fim que quando termina já aponta pra *prox e volta pro primeiro)
typedef struct NoCircular {
    Pessoa          dados;
    struct NoCircular *prox;
} NoCircular;
 
typedef struct {
    NoCircular *fim;   // aqui é pra apontar pra primeiro ou "fechar o círculo"
    int         tamanho;
} FilaCircular;
 
//aqui vai as funções pra fila normal. repare que inicio e fim começam com NULL e tamanho é zerado pois não tem nada ainda
 
void inicializarFilaNormal(FilaNormal *fila) {
    fila->inicio  = NULL;
    fila->fim     = NULL;
    fila->tamanho = 0;
}
 
int filaVaziaNormal(const FilaNormal *fila) {
    return fila->tamanho == 0;
}
 
//pra enfileirar pelo fim. tem alocação dinâmica, já que vai passar elemento pro fim.
int enfileirarNormal(FilaNormal *fila, Pessoa p) {
    NoNormal *novo = (NoNormal *)malloc(sizeof(NoNormal));
    if (!novo) {
        printf("Erro, a memória é insuficiente pra operação!\n");
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
 
//aqui desenfileira do início, seguindo o FIFO. repare que tem o free para a condição, para poder liberar a memória pra aplicação reusar futuramente.
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
 
//as funções para a fila circular simples. repare que não tem mais o ponteiro inicio, já que é circular.
 
void inicializarFilaCircular(FilaCircular *fila) {
    fila->fim      = NULL;
    fila->tamanho  = 0;
}
 
int filaVaziaCircular(const FilaCircular *fila) {
    return fila->tamanho == 0;
}
 
//pra enfileirar pelo fim.
int enfileirarCircular(FilaCircular *fila, Pessoa p) {
    NoCircular *novo = (NoCircular *)malloc(sizeof(NoCircular));
    if (!novo) {
        printf("Erro, a memória é insuficiente pra operação\n");
        return 0;
    }
    novo->dados = p;
 
    if (filaVaziaCircular(fila)) {
        novo->prox = novo;   //pra o nó da fila apontar pra ele mesmo.
    } else {
        novo->prox    = fila->fim->prox;  // novo->prox = antigo início e assim enfileira.
        fila->fim->prox = novo;             
    }
    fila->fim = novo;        //novo é agora o fim pra poder fechar o circulo
    fila->tamanho++;
    return 1;
}
 
// pra desenfileirar do início agora. tem o free pra liberar memória
int desenfileirarCircular(FilaCircular *fila, Pessoa *dest) {
    if (filaVaziaCircular(fila)) return 0;
 
    NoCircular *inicio = fila->fim->prox;  //primeiro elemento
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
 
//funções pra usos (visualização, horário...).
 
void obterHorario(char *buf, int tam) {
    time_t t   = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buf, tam, "%H:%M:%S", tm_info);
}
 
void exibirAtendimento(const Pessoa *p, int guiche) {
    printf("  %-10d %-12c %-20s  [Guichê %d]\n",
           p->senha,
           p->tipo,
           p->horario,
           guiche);
}
 
void exibirCabecalho(void) {
    printf("\n  %-10s %-12s %-20s  %s\n",
           "Senha", "Tipo", "Horário", "Guichê");
    printf("  %s\n", "----------------------------------------------------");
}
 
//para cadastrar as pessoas (pela struct)
 
static int proximaSenhaNormal      = 1001;
static int proximaSenhaPreferencial = 101;
 
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
 
//para a lógica do processo de atender a pessoa (2 normais pra 1 preferencial).
 
void realizarAtendimento(FilaNormal *fn, FilaCircular *fp) {
    Pessoa p;
    int atendidos = 0;
 
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║             INICIANDO ATENDIMENTO                    ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    exibirCabecalho();
 
    /*
      ciclo: 2 normais pra 1 preferencial
      se uma fila esvazia, continua pela outra.
     */
    while (!filaVaziaNormal(fn) || !filaVaziaCircular(fp)) {
 
        //atende até 2 senhas normais.
        int chamadas_normais = 0;
        while (chamadas_normais < 2 && !filaVaziaNormal(fn)) {
            desenfileirarNormal(fn, &p);
            exibirAtendimento(&p, 1);
            chamadas_normais++;
            atendidos++;
        }
 
        //atende 1 senha preferencial (quando há). 
        if (!filaVaziaCircular(fp)) {
            desenfileirarCircular(fp, &p);
            exibirAtendimento(&p, 2);
            atendidos++;
        }
    }
 
    printf("  %s\n", "----------------------------------------------------");
    printf("  Total atendido: %d pessoa(s)\n\n", atendidos);
}
 
//para mostrar as filas se formando.
 
void exibirFilaNormal(const FilaNormal *fila) {
    printf("\n  Fila Normal (%d pessoa(s) aguardando):\n", fila->tamanho);
    if (filaVaziaNormal(fila)) {
        printf("    [vazia]\n");
        return;
    }
    NoNormal *atual = fila->inicio;
    int pos = 1;
    while (atual) {
        printf("    %d. Senha %d | %s\n", pos++, atual->dados.senha, atual->dados.horario);
        atual = atual->prox;
    }
}
 
void exibirFilaCircular(const FilaCircular *fila) {
    printf("\n  Fila Preferencial (%d pessoa(s) aguardando):\n", fila->tamanho);
    if (filaVaziaCircular(fila)) {
        printf("    [vazia]\n");
        return;
    }
    NoCircular *inicio = fila->fim->prox;
    NoCircular *atual  = inicio;
    int pos = 1;
    do {
        printf("    %d. Senha %d | %s\n", pos++, atual->dados.senha, atual->dados.horario);
        atual = atual->prox;
    } while (atual != inicio);
}
 
//impressão do menu.
 
void exibirMenu(void) {
    printf("\n╔══════════════════════════════════╗\n");
    printf("║    BANCO ÁGIL - SENHAS           ║\n");
    printf("╠══════════════════════════════════╣\n");
    printf("║  1. Emitir senha NORMAL          ║\n");
    printf("║  2. Emitir senha PREFERENCIAL    ║\n");
    printf("║  3. Chamar próximas senhas       ║\n");
    printf("║  4. Exibir filas                 ║\n");
    printf("║  0. Sair                         ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf("  Opção: ");
}
 
//para rodar o programa principal.
 
int main() {
    FilaNormal   filaNormal;
    FilaCircular filaPref;
 
    inicializarFilaNormal(&filaNormal);
    inicializarFilaCircular(&filaPref);
 
    int opcao;
 
    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }
 
        switch (opcao) {
            case 1: {
                Pessoa p = criarPessoaNormal();
                if (enfileirarNormal(&filaNormal, p)) {
                    printf("\n  ✔ Senha NORMAL %d emitida às %s\n", p.senha, p.horario);
                }
                break;
            }
            case 2: {
                Pessoa p = criarPessoaPreferencial();
                if (enfileirarCircular(&filaPref, p)) {
                    printf("\n  ✔ Senha PREFERENCIAL %d emitida às %s\n", p.senha, p.horario);
                }
                break;
            }
            case 3: {
                if (filaVaziaNormal(&filaNormal) && filaVaziaCircular(&filaPref)) {
                    printf("\n  Ambas as filas estão vazias. Nada a atender.\n");
                } else {
                    realizarAtendimento(&filaNormal, &filaPref);
                }
                break;
            }
            case 4: {
                exibirFilaNormal(&filaNormal);
                exibirFilaCircular(&filaPref);
                break;
            }
            case 0:
                printf("\n  Encerrando o sistema. Até logo!\n\n");
                break;
            default:
                printf("\n  Opção inválida. Tente novamente.\n");
        }
 
    } while (opcao != 0);
 
    //para liberação da memória que resta..
    liberarFilaNormal(&filaNormal);
    liberarFilaCircular(&filaPref);
 
    return 0;
}
