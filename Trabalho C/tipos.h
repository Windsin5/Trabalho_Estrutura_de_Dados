#ifndef TIPOS_H
#define TIPOS_H

/* =========================================================
   tipos.h  –  structs e constantes compartilhadas
   ========================================================= */

#define HORARIO_TAM 20

typedef struct Pessoa {
    int  senha;
    char tipo;          /* 'N' = normal | 'P' = preferencial */
    char horario[HORARIO_TAM];
} Pessoa;

#endif /* TIPOS_H */
