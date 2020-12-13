#include "matrizv3.h"

matriz *msomar (matriz *mat_a, matriz *mat_b, int tipo);
matriz *multiplicarSeq (matriz *matA, matriz *matB);

matriz *multiplicaBloco (matriz_bloco_t *matA, matriz_bloco_t *matB);

int multiplicaBlocoAux (int **matA, bloco_t *bA, int **matB, bloco_t *bB, matriz *matR);