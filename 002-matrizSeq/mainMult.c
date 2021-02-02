#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv3.h"
#include "matrizv3.h"
#include "matriz-operacoesv3.h"


int main(int argc, char *argv[]) {
	matriz *matA, *matB;
	matriz_bloco_t *matrizesParticionadas;
	// char filename[100];
	// int N, M, La, Lb;
	// double start_time, end_time;

	if (argc != 4){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b> <divisor>\n", argv[0]);
		exit (1);
	}
	int divisor = atoi(argv[3]);

	matA = leMatriz(argv[1]);
	matB = leMatriz(argv[2]);

	matriz *matC = multiplicarSeq(matA, matB);
	// mimprimir(matC);

	// puts("\n\n");

	matrizesParticionadas = particionarMatrizVR(matA, matB, divisor);
	puts("Matriz Bloco A");
	imprimirBlocos(&matrizesParticionadas[0]);
	puts("Matriz Bloco B");
	imprimirBlocos(&matrizesParticionadas[1]);

	puts("Multiplicacao de matriz em bloco \n");
	matriz *resultado = multiplicaBloco(&matrizesParticionadas[0], &matrizesParticionadas[1]);
	matriz *resultadoParalel = multiplicarBlocoThreads(&matrizesParticionadas[0], &matrizesParticionadas[1]);
	// mimprimir(resultado);
	mcomparar(matC, resultado);
	mcomparar(matC, resultadoParalel);

	// Liberar submatriz ja liberar a **matriz logo nao pode mliberar a matA e matB
	liberarSubmatriz(&matrizesParticionadas[0]);
	liberarSubmatriz(&matrizesParticionadas[1]);
	
	mliberar(resultado);
	mliberar(matC);
	free(resultado);
	return 0;
}


