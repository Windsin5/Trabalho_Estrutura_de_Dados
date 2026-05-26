#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "crud-functions.h"

int main(){

    // Configura o console para usar UTF-8, permitindo a exibição correta de caracteres acentuados
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    while(1){
        menu(); // Exibe o menu de opções para o usuário
        int opcao;
        printf("Escolha uma opção: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        static musica *playlist = NULL; // Declaração estática da playlist, guardando o ultimo valor atribuído para ser usado em todas as chamadas

        switch(opcao){
            case 1:
                criarplaylist(&playlist); // Chama a função para criar uma nova playlist
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
                
            case 7:
                
            case 0:
                
            default:
                printf("Opção inválida. Tente novamente.\n"); // Mensagem de erro para opções inválidas
        }
    }
    
    return 0;
}