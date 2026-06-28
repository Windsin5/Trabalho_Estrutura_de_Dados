#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "crud-functions.h"
#include "file-functions.h"

int main(){

    // Configura o console para usar UTF-8, permitindo a exibição correta de caracteres acentuados
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    static musica *playlist = NULL; // Declaração estática da playlist, guardando o ultimo valor atribuído para ser usado em todas as chamadas
    char nomeArquivo[100];
    extern char playlistNome[100]; // Declaração externa da variável global para acessar o nome da playlist
    
    while(1){
        menu(); // Exibe o menu de opções para o usuário
        int opcao;
        printf("Escolha uma opção: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        switch(opcao){
            case 1:
                criarplaylist(&playlist); // Chama a função para criar uma nova playlist
                snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.csv", playlistNome); // Gera o nome do arquivo CSV com base no nome da playlist
                criarArquivo(nomeArquivo); // Cria o arquivo CSV para a nova playlist
                break;
            case 2:
                exibirPlaylist(playlist); // Chama a função para exibir a playlist atual
                break;
            case 3:
                inserirMusicanoInicio(&playlist); // Chama a função para inserir uma música no início da playlist
                break;
            case 4:
                inserirMusicanoMeio(&playlist); // Chama a função para inserir uma música no meio da playlist
                break;
            case 5:
                inserirMusicaNoFim(&playlist); // Chama a função para inserir uma música no fim da playlist
                break;
            case 6:
                 buscarMusica(playlist);// Chama a função responsável por buscar uma música na playlist por ID, nome ou artista
                 break;
            case 7:
                atualizarMusica(&playlist);// Chama a função para atualizar uma música existente
                break;
            case 8:
    // deletar música (seu amigo vai fazer)
                break;

            case 9:
                 salvarArquivo(playlist, nomeArquivo); // Chama a função para salvar a playlist atual no arquivo CSV
                break;

            case 10:
                    printf("Digite o nome do arquivo da playlist a ser carregado: ");
                    scanf(" %[^\n]", nomeArquivo);// Lê o nome do arquivo da playlist
                    lerArquivo(&playlist, nomeArquivo);// Chama a função para carregar a playlist do arquivo CSV, substituindo a playlist atual na memória
                break;     
            case 0:
                liberarMemoria(&playlist); // Chama a função para liberar a memória alocada para a playlist antes de sair do programa
                printf("Saindo do programa...\n");
                exit(0); // Encerra o programa
                break;
            default:
                printf("Opção inválida. Tente novamente.\n"); // Mensagem de erro para opções inválidas
        }
    }
    
    return 0;
}