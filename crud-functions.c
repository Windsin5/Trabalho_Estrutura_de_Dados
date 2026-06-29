#include "crud-functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char playlistNome[100]; // Variável global para armazenar o nome da playlist, permitindo que seja acessada em todas as funções

void menu() {
    printf("\n\nMenu de Opções:\n\n");
    printf("1. Criar playlist\n");
    printf("2. Exibir playlist\n");
    printf("3. Inserir música no início da playlist\n");
    printf("4. Inserir música no meio da playlist\n");
    printf("5. Inserir música no fim da playlist\n");
    printf("6. Atualizar música na playlist\n");
    printf("7. Deletar música da playlist\n");
    printf("8. Salvar playlist em arquivo\n");
    printf("9. Carregar playlist de arquivo\n");
    printf("0. Sair\n\n");
}

void criarplaylist(musica **playlist) {
    printf("Digite o nome da playlist: ");
    scanf(" %[^\n]", playlistNome);
    *playlist = NULL; 
}

void exibirPlaylist(musica *playlist) {
    if (playlist == NULL) {
        printf("A playlist < %s > está vazia.\n", playlistNome);
        return;
    }
    musica *atual = playlist; // Inicia a exibição a partir do primeiro nó da playlist

    printf("\n---< %s >---\n\n", playlistNome); // Exibe o nome da playlist

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

// Função para criar um novo nó que armazena uma música

musica* criarMusica(int id, char *nome, char *artista, int duracao, char *genero) {
    musica *novaMusica = (musica *)malloc(sizeof(musica));  // Aloca memória para a nova música
    if (novaMusica == NULL) {   // Verifica se a alocação de memória foi bem-sucedida
        printf("Erro ao alocar memória para a nova música.\n");
        exit(1); 
    }
    
    novaMusica->id = id;    // Atribui o ID à nova música

    strncpy(novaMusica->nome, nome, sizeof(novaMusica->nome) - 1);  // Copia o nome para a nova música, -1 garante que não ultrapasse o tamanho do array
    novaMusica->nome[sizeof(novaMusica->nome) - 1] = '\0';  // Garante que a string seja terminada com null

    strncpy(novaMusica->artista, artista, sizeof(novaMusica->artista) - 1);
    novaMusica->artista[sizeof(novaMusica->artista) - 1] = '\0';

    novaMusica->duracao = duracao;  // Atribui a duração à nova música
    strncpy(novaMusica->genero, genero, sizeof(novaMusica->genero) - 1);
    novaMusica->genero[sizeof(novaMusica->genero) - 1] = '\0'; 

    novaMusica->proxima = NULL;     // Inicializa o ponteiro para a próxima música como NULL
    novaMusica->anterior = NULL;    // Inicializa o ponteiro para a música anterior como NULL

    return novaMusica;  // Retorna o ponteiro para a nova música criada
}

int verificarID(musica *playlist, int id) {
    musica *atual = playlist;
    while (atual != NULL) {
        if (atual->id == id) {
            printf("ID já existe. Por favor, escolha um ID diferente.\n");
            return 1; // Retorna 1 para indicar que o ID já existe
        }
        atual = atual->proxima;
    }
    return 0; // Retorna 0 para indicar que o ID não existe
}

// Funções para inserir a música no início, meio e fim da playlist

void inserirMusicanoInicio(musica **playlist) {
    int id, duracao;
    char nome[100], artista[100], genero[50];

     while (getchar() != '\n'); // Limpa o buffer de entrada para evitar problemas com scanf

    printf("\n--- INSERIR NO INÍCIO ---\n");
    printf("Digite o ID: ");
    scanf("%d", &id);
    if (verificarID(*playlist, id) == 1) {
        return; // Se o ID já existe, retorna para o menu principal
    }
    printf("Digite o Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite o Artista: ");
    scanf(" %[^\n]", artista);
    printf("Digite a Duração (segundos): ");
    scanf("%d", &duracao);
    printf("Digite o Gênero: ");
    scanf(" %[^\n]", genero);

    musica *novo = criarMusica(id, nome, artista, duracao, genero);

    if (*playlist != NULL) {    // Se a playlist não estiver vazia, ajusta os ponteiros para inserir a nova música no início
        novo->proxima = *playlist;  // Aponta o próximo da nova música para a atual primeira música
        (*playlist)->anterior = novo; // Aponta o anterior da atual primeira música para a nova música
    }
    *playlist = novo;   // Atualiza o ponteiro da playlist para apontar para a nova música, que agora é a primeira da lista
    printf("Música inserida no início!\n");
}

void inserirMusicaNoFim(musica **playlist) {
    // Verifica se a playlist está vazia
    if (*playlist == NULL) {
        printf("A playlist está vazia. Adicione uma música no início primeiro.\n");
        inserirMusicanoInicio(playlist);
        return;
    }

     while (getchar() != '\n'); // Limpa o buffer de entrada para evitar problemas com scanf

    int id, duracao;
    char nome[100], artista[100], genero[50];

    printf("\n--- INSERIR NO FIM ---\n");
    printf("Digite o ID: ");
    scanf("%d", &id);
    if (verificarID(*playlist, id) == 1) {
        return; // Se o ID já existe, retorna para o menu principal
    }
    printf("Digite o Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite o Artista: ");
    scanf(" %[^\n]", artista);
    printf("Digite a Duração (s): ");
    scanf("%d", &duracao);
    printf("Digite o Gênero: ");
    scanf(" %[^\n]", genero);

    musica *novo = criarMusica(id, nome, artista, duracao, genero);

    // Percorre a playlist até o final para inserir a nova música
    musica *atual = *playlist;
    while (atual->proxima != NULL) {    // Continua percorrendo enquanto não chegar ao final da lista
        atual = atual->proxima;
    }
    // Insere a nova música no final da playlist
    atual->proxima = novo;
    novo->anterior = atual;

    printf("Música inserida no fim!\n");
}

void inserirMusicanoMeio(musica **playlist) {
    // Verifica se a playlist está vazia
    if (*playlist == NULL) {
        printf("A playlist está vazia. Adicione uma música no início primeiro.\n");
        inserirMusicanoInicio(playlist);
        return;
    }

    int id, duracao, posicao;
    char nome[100], artista[100], genero[50];

     while (getchar() != '\n'); // Limpa o buffer de entrada para evitar problemas com scanf

    // Menu para escolher a posição de inserção
     printf("\n--- INSERIR NO MEIO ---\n");
    printf("Digite a posição para inserir (1 para início): ");
    scanf("%d", &posicao);
    //verifica se a posição é menor ou igual a 1, se for, insere no início
    if (posicao <= 1) {
        inserirMusicanoInicio(playlist);
        return;
    }

    // Menu para criar a música a ser inserida
    printf("Digite o ID: ");
    scanf("%d", &id);
    if (verificarID(*playlist, id) == 1) {
        return; // Se o ID já existe, retorna para o menu principal
    }
    printf("Digite o Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite o Artista: ");
    scanf(" %[^\n]", artista);
    printf("Digite a Duração (s): ");
    scanf("%d", &duracao);
    printf("Digite o Gênero: ");
    scanf(" %[^\n]", genero);
    //cria um novo nó para a música a ser inserida
    musica *novo = criarMusica(id, nome, artista, duracao, genero);

    musica *atual = *playlist;
    int contador = 1;
    //percorre a playlist até a posição desejada ou até o final da lista
    while (atual != NULL && contador < posicao) {
        atual = atual->proxima;
        contador++;
    }

    // Se atual for NULL, significa que a posição é maior que o número de músicas na playlist, então insere no fim
    if (atual == NULL) {
        musica *fim = *playlist;
        while (fim->proxima != NULL) {
            fim = fim->proxima;
        }
        fim->proxima = novo;
        novo->anterior = fim;
        printf("Música inserida no fim!\n");
        return;
    }
    // Insere a nova música antes do nó atual
    novo->proxima = atual;
    novo->anterior = atual->anterior;
    // Atualiza o nó anterior para apontar para o novo nó
    if (atual->anterior != NULL) {
        atual->anterior->proxima = novo;
    } else {
        *playlist = novo; // Se o nó atual for o primeiro da lista, atualiza o ponteiro da playlist para o novo nó
    }
    
    atual->anterior = novo; // Atualiza o nó atual para apontar para o novo nó
    printf("Música inserida na posição %d!\n", posicao);
}

void excluirMusica(musica **playlist, int id) {
    if(*playlist == NULL){
        printf("A playlist está vazia.\n");
        return;
    }

    musica *atual = *playlist;

    // Percorre a lista procurando o id
    while (atual != NULL && atual->id != id) {
        atual = atual->proxima;
    }

    if(atual == NULL){
        printf("Música com ID %d não encontrada.\n", id);
        return;
    }
    // Ajusta os ponteiros para remover o nó da lista
    if(atual->anterior != NULL) {
        atual->anterior->proxima = atual->proxima;
    } 
    else {
        // Se o nó a ser removido for o primeiro da lista, atualiza o ponteiro da playlist para o próximo nó
        *playlist = atual->proxima;
    }
    // Ajusta o ponteiro anterior do próximo nó, se existir
    if (atual->proxima != NULL) {
        atual->proxima->anterior = atual->anterior;
    }

    free(atual);
    printf("Música com ID %d removida com sucesso.\n", id);
}

void atualizarMusica(musica *playlist) {
    if (playlist == NULL) {
        printf("A playlist está vazia.\n");
        return;
    }

    int opcao, id, duracao;
    char busca[100];

    printf("\n--- ATUALIZAR MÚSICA ---\n");
    printf("1 - Buscar por ID\n");
    printf("2 - Buscar por nome\n");
    printf("3 - Buscar por artista\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    // Solicita ao usuário a opção de busca e lê a entrada
    switch (opcao) {
        case 1:
            printf("Digite o ID: ");
            scanf("%d", &id);
            break;
        case 2:
            printf("Digite o nome da música: ");
            scanf(" %[^\n]", busca);
            break;
        case 3:
            printf("Digite o artista: ");
            scanf(" %[^\n]", busca);
            break;
        default:
            printf("Opção inválida.\n");
            return;
    }

    musica *atual = playlist;
    int encontrou = 0;

    // Percorre a playlist procurando a música com base na opção escolhida
    while (atual != NULL) {
        switch (opcao) {
            case 1:
                if (atual->id == id) encontrou = 1; // Se o ID da música atual for igual ao ID buscado, define encontrou como 1
                break;
            case 2:
                if (strcmp(atual->nome, busca) == 0) encontrou = 1; // Se o nome da música atual for igual ao nome buscado, define encontrou como 1
                break;
            case 3:
                if (strcmp(atual->artista, busca) == 0) encontrou = 1;
                break; 
        }
        if(encontrou == 1){
            break; // Se achou, para o while na hora
        }
        atual = atual->proxima;
    }
    if (encontrou != 1){
        printf("Música não encontrada.\n");       
        while (getchar() != '\n'); // Limpa o buffer de entrada para evitar problemas com scanf
        return;
    }

    printf("\nMúsica encontrada: %s - %s\n", atual->nome, atual->artista);
    printf("--- Insira os novos dados ---\n");

    printf("Novo nome: ");
    scanf(" %[^\n]", atual->nome);

    printf("Novo artista: ");
    scanf(" %[^\n]", atual->artista);

    printf("Nova duração (segundos): ");
    scanf("%d", &atual->duracao);

    printf("Novo gênero: ");
    scanf(" %[^\n]", atual->genero);

    printf("Música atualizada com sucesso!\n");
}

void liberarMemoria(musica **playlist) {
    musica *atual = *playlist;  // Inicia a liberação de memória a partir do primeiro nó da playlist
    while (atual != NULL) {
        musica *proxima = atual->proxima; // Armazena o ponteiro para a próxima música antes de liberar a memória da música atual
        free(atual);
        atual = proxima;
    }
    *playlist = NULL;   // Após liberar toda a memória, define o ponteiro da playlist como NULL para evitar acessos inválidos
}