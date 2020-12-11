#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv3.h"
#include "matrizv3.h"
#include "matriz-operacoesv3.h"


int main(int argc, char *argv[]) {
	// DECLARAÇÃO de VARIÁVEIS
	matriz *matA, *matB;
	// char filename[100];
	// int N, M, La, Lb;
	// double start_time, end_time;

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

	matA = leMatriz(argv[1]);
	matB = leMatriz(argv[2]);


	matriz *matC = multiplicarSeq(matA, matB);
	mimprimir(matC);

	mliberar(matC);
	mliberar(matA);
	mliberar(matB);
	// free(mat_mult);

	return 0;
}


