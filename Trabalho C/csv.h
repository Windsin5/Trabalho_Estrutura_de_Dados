#ifndef CSV_H
#define CSV_H

/* =========================================================
   csv.h  –  persistência em arquivo CSV
   ---------------------------------------------------------
   Formato do arquivo (separador ';'):
     senha;tipo;horario
   Uma linha por pessoa, sem cabeçalho de coluna no arquivo,
   para facilitar o append incremental.
   ========================================================= */

#include "fila_normal.h"
#include "fila_circular.h"

#define CSV_ARQUIVO "banco_agil_filas.csv"

/*
  Salva o conteúdo ATUAL das duas filas no CSV.
  Modo "w": sobrescreve o arquivo a cada chamada.
  Retorna 1 em sucesso, 0 em falha.
*/
int csvSalvarFilas(const FilaNormal *fn, const FilaCircular *fp);

/*
  Salva um único registro de atendimento concluído.
  Modo "a": acrescenta ao fim do arquivo de histórico.
  Retorna 1 em sucesso, 0 em falha.
*/
int csvSalvarAtendimento(const Pessoa *p, const char *arquivo);

#endif /* CSV_H */
