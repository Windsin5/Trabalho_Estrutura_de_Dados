#include "crud-functions.h"

void exibirPlaylist(musica *playlist) {
    if (playlist == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }
    musica *atual = playlist;
    while (atual != NULL) {
        printf("ID: %d\n", atual->id);
        printf("Nome: %s\n", atual->nome);
        printf("Artista: %s\n", atual->artista);
        printf("Duração: %d segundos\n", atual->duracao);
        printf("Gênero: %s\n", atual->genero);
        printf("-------------------------\n");
        atual = atual->proxima;
    }
}

musica* criarMusica(int id, char *nome, char *artista, int duracao, char *genero) {
    musica *novaMusica = (musica *)malloc(sizeof(musica));
    if (novaMusica == NULL) {
        printf("Erro ao alocar memória para a nova música.\n");
        exit(1); 
    }
    
    novaMusica->id = id;
    
    strncpy(novaMusica->nome, nome, sizeof(novaMusica->nome) - 1);
    novaMusica->nome[sizeof(novaMusica->nome) - 1] = '\0'; 
    
    strncpy(novaMusica->artista, artista, sizeof(novaMusica->artista) - 1);
    novaMusica->artista[sizeof(novaMusica->artista) - 1] = '\0'; 
    
    novaMusica->duracao = duracao;
    
    strncpy(novaMusica->genero, genero, sizeof(novaMusica->genero) - 1);
    novaMusica->genero[sizeof(novaMusica->genero) - 1] = '\0'; 
    
    novaMusica->proxima = NULL;
    novaMusica->anterior = NULL;
    
    return novaMusica;
}