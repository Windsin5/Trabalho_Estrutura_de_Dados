#include <stdio.h>
#include "file-functions.h"
#include "crud-functions.h"

extern char playlistNome[100]; // Declaração externa da variável global para acessar o nome da playlist

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
    fprintf(arquivo, "id;nome;artista;duracao;genero\n"); // Escreve o cabeçalho no arquivo CSV
    return arquivo;
}  

void lerArquivo(musica **playlist, char *nomeArquivo){

    // Corta a string depois do ponto, removendo a extensão do arquivo para usar como nome da playlist
    strncpy(playlistNome, nomeArquivo, sizeof(playlistNome) - 1);
    playlistNome[sizeof(playlistNome) - 1] = '\0';
    char *ponto = strrchr(playlistNome, '.');
    if (ponto != NULL) {
        *ponto = '\0'; 
    }

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

    int id, duração;
    char nome[100], artista[100], genero[100];
    
    while(fgets(linha, sizeof(linha), arquivo) != NULL){
        if(sscanf(linha, "%d;%[^;];%[^;];%d;%[^\n]", &id, nome, artista, &duração, genero) == 5){
            musica *novaMusica = criarMusica(id, nome, artista, duração, genero); // Cria uma nova música com os dados lidos do arquivo
            if (*playlist == NULL) { // Se a playlist estiver vazia, a nova música se torna o primeiro nó
                *playlist = novaMusica;
            } else { // Caso contrário, percorre a playlist até o final e insere a nova música
                musica *atual = *playlist;
                while (atual->proxima != NULL) {
                    atual = atual->proxima;
                }
                atual->proxima = novaMusica; // Insere a nova música no final da playlist
                novaMusica->anterior = atual; // Ajusta o ponteiro anterior da nova música para apontar para a última música da playlist
            }
        }
    }

    fclose(arquivo); // Fecha o arquivo após a leitura dos dados
    printf("Playlist carregada com sucesso do arquivo %s\n", nomeArquivo);
}

void salvarArquivo(musica *playlist, char *nomeArquivo){
    FILE *arquivo = abrirArquivo(nomeArquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao salvar o arquivo %s \n", nomeArquivo);
        return;
    }

    fprintf(arquivo, "id;nome;artista;duracao;genero\n"); // Escreve o cabeçalho no arquivo CSV
    musica *atual = playlist;

    while(atual != NULL){
        fprintf(arquivo, "%d;%s;%s;%d;%s\n", atual->id, atual->nome, atual->artista, atual->duracao, atual->genero); // Escreve os dados da música no arquivo CSV
        atual = atual->proxima;
    }

    fclose(arquivo); // Fecha o arquivo após salvar os dados
    printf("Playlist salva com sucesso no arquivo %s\n", nomeArquivo);

}