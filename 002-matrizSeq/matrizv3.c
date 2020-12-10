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

int mliberar (mymatriz *matriz) {
	for (int i=0; i < matriz->lin; i++) {
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

// from the matrix generate the submatrix
int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco){
	return 1;
}

// print the submatrix
int imprimir_submatriz (matriz_bloco_t *submatriz){
	return 1;
}

// Define a number of sub matrix and generate a vector of these submatrix
matriz_bloco_t **particionar_matriz (int **matriz, int mLin, int mCol, int orientacao, int div){
	//
	return (matriz_bloco_t **) NULL;
};

matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz);

int imprimir_bloco (matriz_bloco_t *submatriz){
	if (!submatriz || !submatriz->bloco){
		puts("Passado ponteiro nulo em Imprimir Bloco");
	}

	return 1;
}

matriz_bloco_t **constroi_submatriz (int **matriz, int mLin, int mCol, int div);
// Para construir a submatriz é necessario na matrix A do tipo MxN subparticionar o N
// Na matrix B NxO é necessario subparticionar o O

matriz_bloco_t **constroi_submatrizv2 (int mLin, int mCol, int div);
