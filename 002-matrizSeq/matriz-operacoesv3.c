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
	if (matA->col != matB->lin){
		puts("Erro: Matrizes incompatíveis!");
		exit(1);
	}

	matriz *matC = NULL;
	matC = (matriz *) malloc(sizeof(matriz));
	if (!matC){
		puts("Sem memoria para alocar matriz C");
		exit(1);
	}

	matC->lin = matA->lin;
	matC->col = matB->col;

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

	for(int M = 0; M < matC->lin; M++){
		for(int O = 0; O < matC->col; O++){
			for(int N = 0; N < matA->col; N++){
				matC->matriz[M][O] += matA->matriz[M][N] * matB->matriz[N][O];
			}
		}
	}

	return matC;
}