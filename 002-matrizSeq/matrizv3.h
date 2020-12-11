#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H
typedef struct {
  int linInicio;
  int linFim;
  int colInicio;
  int colFim;
} bloco_t;

typedef struct {
  int **matriz;
  bloco_t *bloco;
  int col;
  int lin;
  int divisor;
} matriz_bloco_t;

typedef struct {
  int **matriz;
  int lin;
  int col;
} mymatriz;
#endif

// gerência de matrizes
int malocar (mymatriz *matriz);
int mgerar(mymatriz *matriz, int valor);
int mimprimir (mymatriz *matriz);
int mliberar (mymatriz *matriz);
int mzerar (mymatriz *matriz);
int mcomparar (mymatriz *mat_a, mymatriz *mat_b);

// Imprimir a submatriz
int imprimir_submatriz (matriz_bloco_t *submatriz);
// Receber uma matriz_bloco_t e uma orientação que refere a linha ou coluna para particionar nesse sentido
// Retorna um vetor bloco_t que é a delimitação das partições da matrix
bloco_t **particionarAux (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor);
// Particionar matrix Versão Raphael, receber as duas matrizes na estrutura mymatriz e um int com o numero de partições
// Retorna uma vetor de matriz_bloco_t contendo as duas matrizes particionadas
matriz_bloco_t *particionarMatrizVR (mymatriz *mA, mymatriz *mB, int div);
matriz_bloco_t **particionar_matrizv3 (mymatriz *matriz, int orientacao, int divisor);
// Libera todas as submatriz
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz);
// Imprime Bloco T
int imprimir_bloco (matriz_bloco_t *submatriz);
// Constroi matriz C
matriz_bloco_t **constroi_submatriz (int **matriz, int mat_lin, int mat_col, int divisor);
// matriz_bloco_t **constroi_submatrizv3 (mymatriz *matriz, int divisor);