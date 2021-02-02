#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef matrizv3_h
#define matrizv3_h
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
} matriz;

typedef struct {
  int **matA;
  int **matB;
  bloco_t *bA;
  bloco_t *bB;
  matriz *matR;
} threadsParam;

// gerência de matrizes
matriz *lerMatriz(char nomeArq[]);
int malocar (matriz *matriz);
int mgerar(matriz *matriz, int valor);
int mimprimir (matriz *matriz);
int mliberar (matriz *matriz);
int mzerar (matriz *matriz);
int mcomparar (matriz *mat_a, matriz *mat_b);


// Imprimir a submatriz
int imprimirSubmatriz (matriz_bloco_t *submatriz, int num);

// Imprime um Bloco T
int imprimirBloco (matriz_bloco_t *submatriz, int num);

// Imprime todos Bloco_T da matriz
int imprimirBlocos (matriz_bloco_t *submatriz);

// Receber uma matriz_bloco_t e uma orientação que refere a linha ou coluna para particionar nesse sentido
// Retorna um vetor bloco_t que é a delimitação das partições da matrix
// int particionarAux (matriz_bloco_t *matriz, int orientacao);

// Particionar matrix Versão Raphael, receber as duas matrizes na estrutura matriz e um int com o numero de partições
// Retorna uma vetor de matriz_bloco_t contendo as duas matrizes particionadas
matriz_bloco_t *particionarMatrizVR (matriz *mA, matriz *mB, int div);

// matriz_bloco_t **particionarMatrizv3 (matriz *matriz, int orientacao, int div);
// Libera todas as submatriz
int liberarSubmatriz (matriz_bloco_t *submatriz);

// Constroi matriz C
// matriz_bloco_t **constroi_submatriz (int **matriz, int mat_lin, int mat_col, int divisor);
// matriz_bloco_t **constroi_submatrizv3 (matriz *matriz, int divisor);
#endif