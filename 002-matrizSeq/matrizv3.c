#include "matrizv3.h"
#include <time.h>

int malocar (mymatriz *matriz) {
	int **newMatriz = NULL;
	newMatriz = (int **) malloc(matriz->lin*sizeof(int *));

	if (!newMatriz) {
		printf("ERROR: Out of memory\n");
		return 1;
	}

	for (int i=0; i < matriz->lin; i++) {
		newMatriz[i] = (int *) malloc(sizeof(int)*matriz->col);
		if (!newMatriz) {
			printf("ERROR: Out of memory\n");
			return 1;
		}
	}

	matriz->matriz = newMatriz;
	return 0;
}

// Popular uma matriz ja criada
int mgerar(mymatriz *matriz, int valor){
	srand( (unsigned)time(NULL) );

	for (int i=0; i < matriz->lin; i++){
		for (int j=0; j < matriz->col; j++){
			if (valor == -9999) matriz->matriz[i][j] = rand() % 10;
			else matriz->matriz[i][j] = valor;
		}
	}

	return 0;
}

int mimprimir (mymatriz *matriz){
	int linha, coluna;
	linha = matriz->lin;
	coluna = matriz->col;

	if (linha > 15) linha = 15;
	if (coluna > 15) coluna = 15;

	for (int j=0; j < coluna; j++){
		printf("\t(%d)", j);
		printf("\n");
	}

	for (int i=0; i < linha; i++) {
		printf("(%d)", i);
		for (int j=0; j < coluna; j++){
			printf("\t%d", matriz->matriz[i][j]);
		}
		printf("\n");
	}

	printf("\n \
	%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n \
	WARNING: Impressão truncada em 15x15! \n \
	WARNING: Último elemento matriz[%d][%d] = %d \n \
	%%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%% %%%%%%%%%%%%\n", \
	matriz->lin-1, matriz->col-1, matriz->matriz[matriz->lin-1][matriz->col-1]);

	return 0;
}

int mliberar (mymatriz *matriz) { for (int i=0; i < matriz->lin; i++) {
		//printf("%p\n", matriz->matriz[i]);
		free(matriz->matriz[i]);
	}
	free(matriz->matriz);
	return 0;
}

int mzerar (mymatriz *matriz){
	return mgerar(matriz,0);
}

int mcomparar (mymatriz *matA, mymatriz *matB){
	for (int i=0; i < matA->lin; i++) {
		for (int j=0; j < matA->col; j++){
			if (matA->matriz[i][j] != matB->matriz[i][j]) {
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!\n", i,j);
				return 1;
			}
		}
	}
	printf("\tVERIFICADO: Matrizes identicas\n");
	return 0;
}

// Popula a matrix de origem e ... Help
int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco){
	return 0;
}

// Imprime a submatriz
int imprimir_submatriz (matriz_bloco_t *submatriz){
	for (int div = 0; div < submatriz->divisor; div++){
		for (int i = submatriz->bloco[div].linInicio; i < submatriz->bloco[div].linFim; i++){
			for (int j = submatriz->bloco[div].colInicio; j < submatriz->bloco[div].colFim; j++){
				printf("%d ", submatriz->matriz[i][j]);
			}
			puts("");
		}
	}
	
	return 0;
}

// Define a number of sub matrix and generate a vector of these submatrix
//
matriz_bloco_t **particionar_matriz (int **matriz, int mLin, int mCol, int orientacao, int div){
	matriz_bloco_t *subMatrizes = NULL;	
	return (matriz_bloco_t **) NULL;
};

// Da free no vetor de bloco_t, na int **matriz e no matriz_bloco_t recebido
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz);

int imprimir_bloco (matriz_bloco_t *submatriz){
	if (!submatriz || !submatriz->bloco){
		puts("Passado ponteiro nulo em Imprimir Bloco");
		return 1;
	}
	
	return 0;
}

// Para construir a submatriz é necessario na matrix A do tipo MxN subparticionar o N
// Na matrix B NxO é necessario subparticionar o N e somar todas as submatrizes
matriz_bloco_t **constroi_submatriz (int **matriz, int mLin, int mCol, int div);

// Gerar uma matriz de tamanho mLin x mCol e particionala em div partes
// retornar um matriz_bloco_t que seria a matriz particionado em blocos
// matriz_bloco_t **constroi_submatrizv3 (int mLin, int mCol, int div);
// MxN							NxO

// Mat A1    Mat A2
// bloco_t *bA = (bloco_t *) malloc(sizeof(bloco_t) * divisor);
// bloco_t *bB = (bloco_t *) malloc(sizeof(bloco_t) * divisor);
// bA[0].linInicio = 0; bA[0].linFim = 5;bA[0].colInicio = 0; bA[0].colFim = 1;
// bA[1].linInicio = 0; bA[1].linFim = 5;bA[1].colInicio = 2; bA[1].colFim = 2;
// bB[0].linInicio = 0; bB[0].linFim = 5;bA[0].colInicio = 0; bA[0].colFim = 1;
// bB[1].linInicio = 0; bB[1].linFim = 5;bA[1].colInicio = 2; bA[1].colFim = 2;
// 5x2		5x1
// 1 2 		3				1 2 3 4 5 6 7 8		Mat B1   
// 1 2 		3				1 2 3 4 5 6 7 8		2x8	
// 1 2 		3				
// 1 2 		3				1 2 3 4 5 6 7 8		1x8
// 1 2 		3

// MatF = (MatA1 * MatB1 + MatA2 * MatB2)