#include <mpi.h>
#include "matriz-operacoesv3.h"
#include "toolsv3.h"

#define ERROR if (error) {goto Final;}

int main(int argc, char** argv) {
  int rank, size, error;
  int* sizesM = (int*)malloc(sizeof(int) * 4);
  matriz* matA, * matB, * matR, *matSeq;
  matriz* Final;
  matriz_bloco_t* matrizesParticionadas;
  double initTime, endTime;
  // MPI_Status status;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  error = 0;
  if (!rank && argc < 3) {
    puts("ERRO: Numero de parametros esta incorreto execute na forma ./mpirun -np 5 mainmpi mat_a3x4.example mat_b4x3.example");
    error = 1;
  }

  MPI_Bcast(&error, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //Verificar Error
  ERROR;

  if (!rank) {
    matA = leMatriz(argv[1]);
    matB = leMatriz(argv[2]);
    sizesM[0] = matA->lin;
    sizesM[1] = matA->col;
    sizesM[2] = matB->lin;
    sizesM[3] = matB->col;
    initTime = wtime();
    matSeq = multiplicarSeq(matA, matB);
    endTime = wtime();
    printf("Tempo execucao: %lf ms\n", endTime - initTime);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  else {
    MPI_Barrier(MPI_COMM_WORLD);
  }

  if (!rank && (matA->col < size || size < 2)) { puts("ERRO: O numero de processos deve ser maior que 1 e menor que N sendo N o tamanho das colunas de MatA e de linhas de matB"); error = 1; }
  MPI_Bcast(&error, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //Verifica Error
  ERROR;

  MPI_Bcast(sizesM, 4, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank) {
    malocarMPI(&matA, sizesM[0], sizesM[1]);
    malocarMPI(&matB, sizesM[2], sizesM[3]);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  else {
    MPI_Barrier(MPI_COMM_WORLD);
  }

  initTime = wtime();
  for (int i = 0; i < sizesM[0]; i++) {
    MPI_Bcast(matA->matriz[i], sizesM[1], MPI_INT, 0, MPI_COMM_WORLD);
  }
  for (int i = 0; i < sizesM[2]; i++) {
    MPI_Bcast(matB->matriz[i], sizesM[3], MPI_INT, 0, MPI_COMM_WORLD);
  }

  matrizesParticionadas = particionarMatrizVR(matA, matB, size);

  malocarMPI(&matR, matA->lin, matB->col);
  multiplicaBlocoAux(matA->matriz, &(matrizesParticionadas[0].bloco[rank]), matB->matriz, &(matrizesParticionadas[1].bloco[rank]), matR);

  int* buff;
  if (!rank) {
    malocarMPI(&Final, matR->lin, matR->col); //Cria uma matriz para alocar todos os endereços do gather
    buff = (int*)malloc(sizeof(int) * size * matR->col);
    // int * teste = (int*) malloc(sizeof(int)) * size * matR->col);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  else {
    MPI_Barrier(MPI_COMM_WORLD);
  }

  for (int i = 0; i < matR->lin; i++) {
    MPI_Gather(matR->matriz[i], matR->col, MPI_INT, buff, matR->col, MPI_INT, 0, MPI_COMM_WORLD);
    if(!rank){
      for (int j = 0; j < matB->col; j++) {
        for (int size_ = 0; size_ < size; size_++) {
          Final->matriz[i][j] += buff[j + size_ * matB->col];
        }
      }
    }
  }

  if (!rank) {
    endTime = wtime();
    printf("Tempo execucao: %lf ms\n", endTime - initTime);
    mcomparar(matSeq, Final);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  else {
    MPI_Barrier(MPI_COMM_WORLD);
  }

Final:
  MPI_Finalize();
  return 0;
}
