#ifndef BUSCA_H
#define BUSCA_H

/* =========================================================
   busca.h  –  funções de busca nas filas
   ========================================================= */

#include "fila_normal.h"
#include "fila_circular.h"

/*
  Busca uma senha em AMBAS as filas e imprime o resultado.
  Retorna 1 se encontrada, 0 se não.
*/
int buscarSenha(const FilaNormal *fn, const FilaCircular *fp, int senha);

/*
  Lista todas as pessoas de um tipo ('N' ou 'P') em ambas as filas.
  Retorna a quantidade encontrada.
*/
int buscarPorTipo(const FilaNormal *fn, const FilaCircular *fp, char tipo);

/*
  Interface interativa: pede ao usuário o critério e chama as funções acima.
*/
void menuBusca(const FilaNormal *fn, const FilaCircular *fp);

#endif /* BUSCA_H */
