#include "matriz-operacoesv3.h"
#include <pthread.h>

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
	matriz *matC = criaMatrizFinal(matA, matB);
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
	// Nao e possivel utilizar criaMatrizFinal pois ela utiliza matrz e nao matriz_bloco_t
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

void *routine(void *args){
	threadsParam *arg = (threadsParam*) args;
	multiplicaBlocoAux(arg->matA, arg->bA, arg->matB, arg->bB, arg->matR);
	return NULL;
};

matriz *multiplicarBlocoThreads (matriz_bloco_t *matA, matriz_bloco_t *matB){
	matriz *matR = (matriz *) malloc(sizeof(matriz) * matA->divisor);
	matriz *final = (matriz *) malloc(sizeof(matriz));
	pthread_t *tIds = (pthread_t*) malloc(sizeof(pthread_t) * matA->divisor);
	threadsParam *params = (threadsParam *) malloc(sizeof(threadsParam) * matA->divisor);
	final->lin = matA->lin;
	final->col = matB->col;
	malocar(final);
	for(int i = 0; i < matA->divisor; i++){
		matR[i].lin = matA->lin;
		matR[i].col = matB->col;
		params[i].matA = matA->matriz;
		params[i].matB = matB->matriz;
		params[i].bA = &(matA->bloco[i]);
		params[i].bB = &(matB->bloco[i]);
		params[i].matR = &(matR[i]);
		malocar(&matR[i]);
	}

	for(int i = 0; i < matA->divisor; i++) pthread_create(&tIds[i], NULL, routine, (void *) &params[i]);

	for(int i = 0; i < matA->divisor; i++) pthread_join(tIds[i], NULL);

	for(int i = 0; i < matA->lin; i++){
		for(int j = 0; j < matB->col; j++){
			for(int divs = 0; divs < matA->divisor; divs++){
				final->matriz[i][j] += matR[divs].matriz[i][j];
			}
		}
	}
	for(int i = 0; i < matA->divisor; i++) mliberar(&matR[i]);
	free(matR);
	free(tIds);
	free(params);
	return final;
}

matriz *criaMatrizFinal(matriz *matA, matriz *matB){
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
	malocar(matC);

	return matC;
}