#ifndef CRUD_FUNCTIONS_H
#define CRUD_FUNCTIONS_H

#include <stdio.h>

typedef struct{
    int id;
    char nome[100];
    char artista[100];
    int duracao; // duração em segundos
    char genero[50];
}musica;

void alocarmemoria(musica **m, int n);
void criarMusica(musica *m);
void exibirMusica(musica *m, int n);
void atualizarMusica(musica *m, int n);
void deletarMusica(musica *m, int n);













#endif