#ifndef CRUD_FUNCTIONS_H
#define CRUD_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct musica {
    int id;
    char nome[100];
    char artista[100];
    int duracao;    // Duração em segundos
    char genero[50];
    struct musica *proxima; 
    struct musica *anterior; 
} musica;

musica* criarMusica(int id, char *nome, char *artista, int duracao, char *genero); 
void exibirPlaylist(musica *playlist);  
void adicionarnaPlaylist(musica **playlist, musica *novaMusica);
void inserirMusicanoInicio(musica **playlist);
void inserirMusicanoMeio(musica **playlist);
void inserirMusicaNoFim(musica **playlist);
void atualizarMusica(musica **playlist, char *nome);
void deletarMusica(musica **playlist, char *nome);

#endif