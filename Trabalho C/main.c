/* =========================================================
   main.c  ?  Banco �gil � Sistema de Senhas
   ---------------------------------------------------------
   compilar com windows:
     gcc main.c fila_normal.c fila_circular.c utils.c csv.c busca.c -o banco_agil
   compilar em sistemas unix:
     gcc main.c fila_normal.c fila_circular.c utils.c csv.c busca.c -o banco_agil
   ========================================================= */

#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "cores.h"
#include "tipos.h"
#include "fila_normal.h"
#include "fila_circular.h"
#include "utils.h"
#include "csv.h"
#include "busca.h"

int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");


    SetConsoleOutputCP(65001);   /* caracteres especiais no Windows */


    cores_inicializar();           /* quando em windows, vai habilitar o ansi e colorir� algumas impress�es  */

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

            /* --- emitir senha normal --- */
            case 1: {
                Pessoa p = criarPessoaNormal();
                if (enfileirarNormal(&filaNormal, p)) {
                    printf(COR_AMARELO
                           "\n  Senha NORMAL %d emitida às %s\n"
                           COR_RESET, p.senha, p.horario);
                }
                break;
            }

            /* --- emitir senha preferencial --- */
            case 2: {
                Pessoa p = criarPessoaPreferencial();
                if (enfileirarCircular(&filaPref, p)) {
                    printf(COR_AZUL
                           "\n  Senha PREFERENCIAL %d emitida às %s\n"
                           COR_RESET, p.senha, p.horario);
                }
                break;
            }

            /* --- chamar próximas senhas --- */
            case 3: {
                if (filaVaziaNormal(&filaNormal) && filaVaziaCircular(&filaPref)) {
                    printf(COR_VERMELHO
                           "\n  Ambas as filas estão vazias. Nada a atender.\n"
                           COR_RESET);
                } else {
                    realizarAtendimento(&filaNormal, &filaPref);
                }
                break;
            }

            /* --- exibir filas --- */
            case 4: {
                exibirFilaNormal(&filaNormal);
                exibirFilaCircular(&filaPref);
                break;
            }

            /* --- buscar senha --- */
            case 5: {
                menuBusca(&filaNormal, &filaPref);
                break;
            }

            /* --- salvar em CSV --- */
            case 6: {
                csvSalvarFilas(&filaNormal, &filaPref);
                break;
            }

            /* --- sair --- */
            case 0:
                printf(COR_VERDE
                       "\n  O Banco Ágil agradece a sua preferência. Até a próxima!\n\n"
                       COR_RESET);
                break;

            default:
                printf(COR_VERMELHO
                       "\n  Essa opção não existe, tente outra opção!\n"
                       COR_RESET);
        }

    } while (opcao != 0);

    /* libera mem�ria remanescente */
    liberarFilaNormal(&filaNormal);
    liberarFilaCircular(&filaPref);

    return 0;
}
