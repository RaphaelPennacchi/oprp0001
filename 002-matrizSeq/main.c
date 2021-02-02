#include "toolsv3.h"
#include "matrizv3.h"
#include "matriz-operacoesv3.h"


int main(int argc, char *argv[]) {
	matriz *matA, *matB;
	matriz_bloco_t *matrizesParticionadas;
	double initTime, endTime;
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
	// mimprimir(matC);
	// puts("\n\n");

	matrizesParticionadas = particionarMatrizVR(matA, matB, divisor);
	// puts("Matriz Bloco A");
	// imprimirBlocos(&matrizesParticionadas[0]);
	// puts("Matriz Bloco B");
	// imprimirBlocos(&matrizesParticionadas[1]);

	puts("seq");
	initTime = wtime();
	matriz *matC = multiplicarSeq(matA, matB);
	endTime = wtime();
	printf("Tempo execucao: %lf ms\n", endTime - initTime);

	initTime = wtime();
	matriz *resultado = multiplicaBloco(&matrizesParticionadas[0], &matrizesParticionadas[1], BLOCO);
	endTime = wtime();
	printf("Tempo execucao: %lf ms\n", endTime - initTime);

	initTime = wtime();
	matriz *resultadoParalel = multiplicaBloco(&matrizesParticionadas[0], &matrizesParticionadas[1], THREADS);
	endTime = wtime();
	printf("Tempo execucao: %lf ms\n", endTime - initTime);

	initTime = wtime();
	matriz *resultadoOpenMp = multiplicaBloco(&matrizesParticionadas[0], &matrizesParticionadas[1], OPENMP);
	endTime = wtime();
	printf("Tempo execucao: %lf ms\n", endTime - initTime);

	puts("\n\tComparar SEQ e BLOCO");
	mcomparar(matC, resultado);
	puts("\tComparar SEQ e THREADS");
	mcomparar(matC, resultadoParalel);
	puts("\tComparar SEQ e OPENMP");
	mcomparar(matC, resultadoOpenMp);

	// Liberar submatriz ja liberar a **matriz logo nao pode mliberar a matA e matB
	liberarSubmatriz(&matrizesParticionadas[0]);
	liberarSubmatriz(&matrizesParticionadas[1]);
	
	mliberar(resultado);
	mliberar(resultadoParalel);
	mliberar(resultadoOpenMp);
	mliberar(matC);
	free(matC);
	free(matA);
	free(matB);
	free(resultado);
	free(resultadoParalel);
	free(resultadoOpenMp);
	free(matrizesParticionadas);
	return 0;
}


