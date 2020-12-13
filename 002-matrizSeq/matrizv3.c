#include "matrizv3.h"
#include <time.h>

int malocar (matriz *matriz) {
	int **newMatriz = NULL;
	newMatriz = (int **) malloc(matriz->lin*sizeof(int *));

	if (!newMatriz) {
		printf("ERROR: Out of memory\n");
		return 1;
	}

	for (int i=0; i < matriz->lin; i++) {
		newMatriz[i] = (int *) calloc(matriz->col, sizeof(int));
		if (!newMatriz) {
			printf("ERROR: Out of memory\n");
			return 1;
		}
	}

	matriz->matriz = newMatriz;
	return 0;
}

// Popular uma matriz ja criada
int mgerar(matriz *matriz, int valor){
	srand( (unsigned)time(NULL) );

	for (int i=0; i < matriz->lin; i++){
		for (int j=0; j < matriz->col; j++){
			if (valor == -9999) matriz->matriz[i][j] = rand() % 10;
			else matriz->matriz[i][j] = valor;
		}
	}

	return 0;
}

int mimprimir (matriz *matriz){
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
	WARNING: Impressão truncada em 15x15! \n \
	WARNING: Último elemento matriz[%d][%d] = %d \n \
	\n", \
	matriz->lin-1, matriz->col-1, matriz->matriz[matriz->lin-1][matriz->col-1]);

	return 0;
}

int mliberar (matriz *matriz) { 
	if(!(matriz->matriz)) return 1;
	for (int i=0; i < matriz->lin; i++) {
		//printf("%p\n", matriz->matriz[i]);
		free(matriz->matriz[i]);
	}
	free(matriz->matriz);
	return 0;
}

int mzerar (matriz *matriz){
	return mgerar(matriz,0);
}

int mcomparar (matriz *matA, matriz *matB){
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

// Imprimir a submatriz, num comeca em 0
int imprimirSubmatriz (matriz_bloco_t *submatriz, int num){
	if (!submatriz || !submatriz->bloco){
		puts("Passado ponteiro nulo em Imprimir Submatriz");
		return 1;
	}

	if( submatriz->divisor <= num){
		puts("Submatriz não existente");
		return 1;
	}

	for (int i = submatriz->bloco[num].linInicio; i < submatriz->bloco[num].linFim; i++){
		for (int j = submatriz->bloco[num].colInicio; j < submatriz->bloco[num].colFim; j++){
			printf("%d ", submatriz->matriz[i][j]);
		}
		puts("");
	}
	
	return 0;
}

// Imprime o Bloco T
int imprimirBloco (matriz_bloco_t *submatriz, int num){
	if (!submatriz || !submatriz->bloco){
		puts("Passado ponteiro nulo em Imprimir Bloco");
		return 1;
	}
	
	if( submatriz->divisor <= num){
		puts("Submatriz não existente");
		return 1;
	}

	printf("Bloco[%d]: li %d lf %d ci %d cf %d\n", num, submatriz->bloco[num].linInicio, 
		submatriz->bloco[num].linFim, submatriz->bloco[num].colInicio, submatriz->bloco[num].colFim);

	return 0;
}

// Imprime o blocosT
int imprimirBlocos (matriz_bloco_t *submatriz){
	if (!submatriz || !submatriz->bloco){
		puts("Passado ponteiro nulo em Imprimir Blocos T");
		return 1;
	}

	for(int i = 0; i < submatriz->divisor; i++){
		if(imprimirBloco(submatriz, i)) return 1;
	}
	return 0;
}

// Da free no vetor de bloco_t, na int **matriz e no matriz_bloco_t recebido
int liberarSubmatriz(matriz_bloco_t *submatriz){
	if (!submatriz || !(submatriz->bloco)){
		puts("Passado ponteiro nulo em Imprimir Bloco");
		return 1;
	}
	if(submatriz->matriz){
		for (int i = 0; i < submatriz->lin; i++) free(submatriz->matriz[i]);
		free(submatriz->matriz);
		submatriz->matriz = NULL;
	}
	free(submatriz->bloco);

	return 0;
}

// Particionar matrix Versão Raphael Renato, receber as duas matrizes na estrutura matriz e um int com o numero de partições
// Retorna uma vetor de matriz_bloco_t contendo as duas matrizes particionadas
matriz_bloco_t *particionarMatrizVR (matriz *mA, matriz *mB, int div){
	if(mA->col != mB->lin){
		puts("Matriz A coluna e Matriz B linha diferem");
		exit(1);
	} if(mA->col > 1 && mA->col < div){
		puts("Numero divisor fora do intervalo 1 < div <= N");
		exit(1);
	}
	matriz_bloco_t *matrizes = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t) * 2);
	if(!matrizes){
		puts("Nao foi possivel alocar matriz_bloco_t");
		exit(1);
	}
	matrizes[0].lin = mA->lin;
	matrizes[0].col= mA->col;
	matrizes[0].matriz = mA->matriz;
	matrizes[1].lin = mB->lin;
	matrizes[1].col= mB->col;
	matrizes[1].matriz = mB->matriz;

	// Todo Talvez não seja necessário a particionar matrix 
	// Todo Pois sempre vamos separa da mesma forma a mA e a mB
	// Todo	É possivel realizar tudo em um for
	for(int i = 0; i < 2; i++){
		matrizes[i].divisor = div;
		matrizes[i].bloco = (bloco_t *) malloc(sizeof(bloco_t) * div);
		if(!matrizes[i].bloco){
			puts("Falha ao alocar memoria para bloco_t");
			exit(1);
		}
		matrizes[i].bloco[0].colInicio = 0;
		matrizes[i].bloco[0].linInicio = 0;
	}
	matrizes[0].bloco[0].linFim = mA->lin;
	matrizes[0].bloco[0].colFim = (mA->col / div);
	matrizes[1].bloco[0].linFim = (mA->col / div);
	matrizes[1].bloco[0].colFim = mB->col;
	for(int i = 2; i <= div; i++){
		// Atribui os valores dos blocos na matriz_blocot_t A
		matrizes[0].bloco[i-1].linInicio = 0;
		matrizes[0].bloco[i-1].linFim = mA->lin;
		matrizes[0].bloco[i-1].colInicio = matrizes[0].bloco[i-2].colFim;
		matrizes[0].bloco[i-1].colFim = (mA->col / div) * i;
		// Atribui os valores dos blocos na matriz_blocot_t B
		matrizes[1].bloco[i-1].linInicio = matrizes[1].bloco[i-2].linFim;
		matrizes[1].bloco[i-1].linFim = (mA->col / div) * i;
		matrizes[1].bloco[i-1].colInicio = 0;
		matrizes[1].bloco[i-1].colFim = mB->col;
	}
	// Os ultimos blocos devem conter como final a linha maxima + 1
	// Pois o range sera da variavel Incio (inclusiva) ate a Final (exclusiva)
	for(int i = 0; i < 2; i++){
		matrizes[i].bloco[div-1].colFim = matrizes[i].col;
		matrizes[i].bloco[div-1].linFim = matrizes[i].lin;
	}

	return matrizes;
}

// matriz_bloco_t **particionarMatrizv3 (matriz *matriz, int orientacao, int div);
// Libera todas as submatriz


// Para construir a submatriz é necessario na matrix A do tipo MxN subparticionar o N
// Na matrix B NxO é necessario subparticionar o N e somar todas as submatrizes resultantes

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

// MatF = (MatA1 * MatB1 + MatA2 * MatB2);
// MatF = (MatC1 + MatC2);