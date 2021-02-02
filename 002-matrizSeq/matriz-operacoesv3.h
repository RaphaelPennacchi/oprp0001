#include "matrizv3.h"
#include <omp.h>
#include <pthread.h>

typedef enum {BLOCO, THREADS, OPENMP} Options;

matriz *multiplicarSeq (matriz *matA, matriz *matB);
matriz *multiplicaBloco (matriz_bloco_t *matA, matriz_bloco_t *matB, Options opcao);
void multiplicaBlocoAux (int **matA, bloco_t *bA, int **matB, bloco_t *bB, matriz *matR);
void *routine(void *args);