# GNU Makefile
# Revisão: ago/2019

MPICC = mpicc
CC = gcc
CCFLAGS = -Wall -O3 -lpthread -fopenmp
LDFLAGS =
TARGET = main gmat help mpi generate

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@


main: main.c matrizv3.o toolsv3.o matriz-operacoesv3.o
			$(CC) $(CCFLAGS) matrizv3.o toolsv3.o matriz-operacoesv3.o main.c -o $@ $(LDFLAGS)

gmat: matrizv3.o toolsv3.o gera_matrizv3.c
		$(CC) $(CCFLAGS) matrizv3.o toolsv3.o gera_matrizv3.c -o $@ $(LDFLAGS)

mpi: 
	$(MPICC) $(CCFLAGS) -o mainmpi mainMPI.c matrizv3.o toolsv3.o matriz-operacoesv3.o

generate: gmat
	./gmat 100 100
	./gmat 1000 1000

help:
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main mat_a3x4.example mat_b4x3.example 2"
	@echo "mpirun -np 4 mainmpi 1000x1000-mat.map 1000x1000-mat.map"

clean:
	rm -f *.o *~ $(TARGET) *.map *.result mainmpi
