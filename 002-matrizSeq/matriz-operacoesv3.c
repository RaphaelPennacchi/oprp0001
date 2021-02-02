#include "matriz-operacoesv3.h"

// Multiplicação das matrizes de forma sequencial
matriz *multiplicarSeq (matriz *matA, matriz *matB) {
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


// Funcao que multiplica o bloco A da matriz A com o bloco B da matriz B e o resultado e armazenado em matR com acesso direto
void multiplicaBlocoAux (int **matA, bloco_t *bA, int **matB, bloco_t *bB, matriz *matR){
	for(int M = 0; M < matR->lin; M++){
		for(int O = 0; O < matR->col; O++){
			for(int N = bA->colInicio; N < bA->colFim; N++){
				matR->matriz[M][O] += matA[M][N] * matB[N][O];
			}
		}
	}
}

// Funcao que contem todas as formas de multiplicao de matrizes em bloco
matriz *multiplicaBloco (matriz_bloco_t *matA, matriz_bloco_t *matB, Options opcao){
	matriz *matR = (matriz *) malloc(sizeof(matriz) * matA->divisor);
	matriz *final = (matriz *) malloc(sizeof(matriz));
	final->lin = matA->lin;
	final->col = matB->col;
	malocar(final);

	switch(opcao){
		case BLOCO:
			puts("bloco");
			for(int i = 0; i < matA->divisor; i++){
				matR[i].lin = matA->lin;
				matR[i].col = matB->col;
				malocar(&matR[i]);
			}
			for(int i = 0; i < matA->divisor; i++){
				multiplicaBlocoAux(matA->matriz, &(matA->bloco[i]), matB->matriz, &(matB->bloco[i]), &matR[i]);
			}
			break;
		case THREADS:
			puts("threads");
			pthread_t *tIds = (pthread_t*) malloc(sizeof(pthread_t) * matA->divisor);
			threadsParam *params = (threadsParam *) malloc(sizeof(threadsParam) * matA->divisor);

			for(int i = 0; i < matA->divisor; i++){
				matR[i].lin = matA->lin;
				matR[i].col = matB->col;
				params[i].matA = matA->matriz;
				params[i].matB = matB->matriz;
				params[i].bA = &(matA->bloco[i]);
				params[i].bB = &(matB->bloco[i]);
				params[i].matR = &matR[i];
				malocar(&matR[i]);
			}

			for(int i = 0; i < matA->divisor; i++) pthread_create(&tIds[i], NULL, routine, (void *) &params[i]);
			for(int i = 0; i < matA->divisor; i++) pthread_join(tIds[i], NULL);

			free(tIds);
			free(params);
			break;
		case OPENMP:
			puts("openmp");
			for(int i = 0; i < matA->divisor; i++){
				matR[i].lin = matA->lin;
				matR[i].col = matB->col;
				malocar(&matR[i]);
			}
			#pragma omp parallel for
				for(int i = 0; i < matA->divisor; i++){
					multiplicaBlocoAux(matA->matriz, &(matA->bloco[i]), matB->matriz, &(matB->bloco[i]), &matR[i]);
				}
			break;
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