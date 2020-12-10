#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv3.h"
#include "matrizv3.h"
#include "matriz-operacoesv3.h"


int main(int argc, char *argv[]) {

	// DECLARAÇÃO de VARIÁVEIS
	mymatriz matA, matB;
	char filename[100];
	FILE *fMat;
	int nrLine;
	int *vetLine = NULL;
	int N, M, La, Lb;
  int la, ca, lb, cb;
	double start_time, end_time;

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

	//                Leitura da Matriz A (arquivo)
	fMat = fopen(argv[1],"r");
	if (fMat == NULL) {
		printf("Error: Na abertura do arquivo %s.", argv[1]);
		exit(1);
	}
	extrai_parametros_matriz(fMat, &la, &ca, &vetLine, &nrLine);
	//return 1;
	matA.matriz = NULL;
	matA.lin = la;
	matA.col = ca;
	if (malocar(&matA)) {
		printf ("ERROR: Out of memory\n");
	}
	filein_matriz (matA.matriz, la, ca, fMat, vetLine, nrLine);
	free (vetLine);
	fclose(fMat);

	//                Leitura da Matriz B (arquivo)
	fMat = fopen(argv[2],"r");
	if (fMat == NULL) {
		printf("Error: Na abertura do arquivo %s.", argv[2]);
		exit(1);
	}
	extrai_parametros_matriz(fMat, &lb, &cb, &vetLine, &nrLine);
	//return 1;
	matB.matriz = NULL;
	matB.lin = lb;
	matB.col = cb;
	if (malocar(&matB)) {
		printf ("ERROR: Out of memory\n");
	}
	filein_matriz (matB.matriz, lb, cb, fMat, vetLine, nrLine);
	free (vetLine);
	fclose(fMat);

	//               Operações de Multiplicação
	// mat_mult = (mymatriz **) malloc (sizeof(mymatriz *)*6);
	// for (int ii=0; ii < 6; ii++) {
	// 	printf("\n ##### multiplicar_t%d de Matrizes #####\n", ii);
	// 	start_time = wtime();
	// 	mat_mult[ii] = mmultiplicar(&mat_a, &mat_a, ii);
	// 	end_time = wtime();
	// 	mimprimir(mat_mult[ii]);
	// 	printf("\tRuntime: %f\n", end_time - start_time);
	// 	sprintf(filename, "mult_t%d.result", ii);
	// 	fmat = fopen(filename,"w");
	// 	fileout_matriz(mat_mult[ii], fmat);
	// 	fclose(fmat);
	// }

  //                Multiplicação de blocos
  // matMult = (mymatriz **) malloc (sizeof(mymatriz *)*6);


	//              Comparação dos resultados
	// printf("\n ##### Comparação dos resultados da Multiplicação de matrizes #####\n");
	// for (int i=1; i<6; i++) {
	// 	printf("[mult_t0 vs mult_t%d]\t", i);
		//mcomparar (mat_mult[0],mat_mult[i]);
	// }

	//                   Liberação de memória
	// for (int ii=0; ii < 6; ii++) {
		// mliberar(mat_mult[ii]);
		// free (mat_mult[ii]);
	// }

	mliberar(&matA);
	mliberar(&matB);
	// free(mat_mult);

	return 0;
}


