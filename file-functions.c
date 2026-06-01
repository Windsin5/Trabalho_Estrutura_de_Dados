#include <stdio.h>
#include "file-functions.h"
#include "crud-functions.h"

FILE *abrirArquivo(char *nomeArquivo, char *modo){
    FILE *arquivo = fopen(nomeArquivo, modo);
    if(arquivo == NULL){
        return NULL;
    }
    return arquivo;
}

FILE *criarArquivo(char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao criar o arquivo %s\n", nomeArquivo);
        return NULL;
    }
    fprintf(arquivo, "id,nome,artista,duracao,genero\n"); // Escreve o cabeçalho no arquivo CSV
    return arquivo;
}  

void lerArquivo(musica **playlist, char *nomeArquivo){
    FILE *arquivo = abrirArquivo(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Arquivo %s não encontrado. Criando um novo arquivo.\n", nomeArquivo);
        FILE *novoArquivo = criarArquivo(nomeArquivo);
        if(novoArquivo == NULL){
            printf("Erro ao criar o arquivo %s\n", nomeArquivo);
            return;
        }
        if (novoArquivo != NULL) {
            fclose(novoArquivo); // Fecha o arquivo recém-criado
        }
        return;
    }
    char linha[500];

    fgets(linha, sizeof(linha), arquivo); // Lê a primeira linha (cabeçalho) e ignora

}

void salvarArquivo(musica **playlist, char *nomeArquivo){
    FILE *arquivo = abrirArquivo(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao salvar o arquivo %s \n", nomeArquivo);
        return;
    }

    fprintf(arquivo, "id;nome;artista;duracao;genero\n"); // Escreve o cabeçalho no arquivo CSV
    musica *atual = *playlist;

    while(atual != NULL){
        fprintf(arquivo, "%d;%s;%s;%d;%s\n", atual->id, atual->nome, atual->artista, atual->duracao, atual->genero); // Escreve os dados da música no arquivo CSV
        atual = atual->proxima;
    }

    fclose(arquivo); // Fecha o arquivo após salvar os dados
    printf("Playlist salva com sucesso no arquivo %s\n", nomeArquivo);

}