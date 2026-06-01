#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H
#include "crud-functions.h" // Inclui o cabeçalho com as definições da estrutura musica e as funções CRUD

#include <stdio.h>

FILE *abrirArquivo(char *nomeArquivo, char *modo);
FILE *criarArquivo(char *nomeArquivo);
void lerArquivo(musica **playlist, char *nomeArquivo);
void salvarArquivo(musica *playlist, char *nomeArquivo);


#endif