#include "matriz-operacoesv3.h"

matriz *msomar(matriz *mat_a, matriz *mat_b, int tipo){
	matriz *mat_c = NULL;

	if ((mat_a->lin != mat_b-> lin) || (mat_a->col != mat_b->col)){
		puts("Erro: Matrizes incompatíveis!");
		exit(1);
	}

	mat_c = (matriz *) malloc (sizeof(matriz));
	mat_c->lin = mat_a->lin;
	mat_c->col = mat_a->col;

	if (malocar(mat_c)) puts("ERROR: Out of memory");

	if (tipo == 1) {
		for (int i=0; i < mat_c->lin; i++) {
		  for (int j=0; j < mat_c->col; j++) {
					mat_c->matriz[i][j] = mat_a->matriz[i][j]+mat_b->matriz[i][j];
		  }
		}
	} else {
		for (int j=0; j < mat_c->col; j++){
			for (int i=0; i < mat_c->lin; i++){
					mat_c->matriz[i][j] = mat_a->matriz[i][j]+mat_b->matriz[i][j];
			}
		}
	}
  return mat_c;
}

// Multiplicação das matrizes de forma sequencial
matriz *multiplicarSeq (matriz *matA, matriz *matB) {
	// Compara se matA col == matB lin   MxN NxO os N tem que ser iguais
	if (matA->col != matB->lin){
		puts("Erro: Matrizes incompatíveis!");
		exit(1);
	}

	// Aloco a matC
	matriz *matC = NULL;
	matC = (matriz *) malloc(sizeof(matriz));
	if (!matC){
		puts("Sem memoria para alocar matriz C");
		exit(1);
	}

	// matC tem tamanho MxO
	matC->lin = matA->lin;
	matC->col = matB->col;

	// Cria a matC->matriz com todos os campos preenchidos com 0
	matC->matriz = (int **) malloc(matC->lin * sizeof(int *));
	if(!matC->matriz){
		puts("Sem memoria para alocar matriz C");
		exit(1);
	}
	for(int i=0; i < matC->lin; i++){
		matC->matriz[i] = (int *) calloc(matC->col, sizeof(int));
		if(!matC->matriz[i]){
			puts("Sem memoria para alocar matriz C");
			exit(1);
		}
	}

	// Realiza a multiplicacao de matA x matB e salva em matC
	for(int M = 0; M < matC->lin; M++){
		for(int O = 0; O < matC->col; O++){
			for(int N = 0; N < matA->col; N++){
				matC->matriz[M][O] += matA->matriz[M][N] * matB->matriz[N][O];
			}
		}
	}

	return matC;
}


int multiplicaBlocoAux (int **matA, bloco_t *bA, int **matB, bloco_t *bB, matriz *matR){
	for(int M = 0; M < matR->lin; M++){
		for(int O = 0; O < matR->col; O++){
			for(int N = bA->colInicio; N < bA->colFim; N++){
				matR->matriz[M][O] += matA[M][N] * matB[N][O];
			}
		}
	}
	return 0;
}


matriz *multiplicaBloco (matriz_bloco_t *matA, matriz_bloco_t *matB){
	matriz *matR = (matriz *) malloc(sizeof(matriz) * matA->divisor);
	matriz *final = (matriz *) malloc(sizeof(matriz));
	final->lin = matA->lin;
	final->col = matB->col;
	malocar(final);
	for(int i = 0; i < matA->divisor; i++){
		matR[i].lin = matA->lin;
		matR[i].col = matB->col;
		malocar(&matR[i]);
	}

	// Todo fazer um loop em cada bloco e colocar em uma funcao aux pra multiplicar
	for(int i = 0; i < matA->divisor; i++){
		multiplicaBlocoAux(matA->matriz, &(matA->bloco[i]), matB->matriz, &(matB->bloco[i]), &matR[i]);
	}

	for(int i = 0; i < matA->lin; i++){
		for(int j = 0; j < matB->col; j++){
			for(int divs = 0; divs < matA->divisor; divs++){
				final->matriz[i][j] += matR[divs].matriz[i][j];
			}
		}
	}
	for(int i = 0; i < matA->divisor; i++) mliberar(&matR[i]);
	free(matR);

	return final;
}