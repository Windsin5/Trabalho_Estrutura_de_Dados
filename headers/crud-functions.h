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

void menu();
musica* criarMusica(int id, char *nome, char *artista, int duracao, char *genero);
void criarplaylist(musica **playlist);
void exibirPlaylist(musica *playlist);  
void inserirMusicanoInicio(musica **playlist);
void inserirMusicanoMeio(musica **playlist);
void inserirMusicaNoFim(musica **playlist);
void atualizarMusica(musica **playlist, char *nome);
void deletarMusica(musica **playlist, char *nome);
void buscarMusica(musica *playlist);
void liberarMemoria(musica **playlist);

#endif