#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv) {
	int rank, size;
	int valorIncial, valorMod, total, nproc;
	MPI_Status sd;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//printf("hellow word, processo %d de %d\n", rank, size);
	fflush(stdout);

	if (rank == 0) { //mestre  
		for (nproc = 1; nproc < size; nproc++) {
			valorIncial = nproc + 10;
			MPI_Send(&valorIncial, 1,MPI_INT, nproc,0,MPI_COMM_WORLD);
			//printf("mestre envo - (%d), para processo - (%d)\n",valorIncial, nproc);
			fflush(stdout);
		}
		total = 0;

		for (nproc = 1; nproc < size; nproc++) {
			MPI_Recv(&valorMod,1,MPI_INT,nproc,MPI_ANY_TAG,MPI_COMM_WORLD, &sd);
			printf("mestre - recebeu o valor modificado (%d)\n", valorMod);

			fflush(stdout);

			total += valorMod;
		}

		printf("Mestre - total processamentos (%d)\n ", total);
		fflush(stdout);


	}
	else { //escravo
		MPI_Recv(&valorIncial, 1, MPI_INT,0,0,MPI_COMM_WORLD,&sd);
		//printf("escravo- (%d) recebi (%d) do mestre \n", rank,valorIncial);
		fflush(stdout);
		
		valorMod = valorIncial * 10;
		MPI_Send(&valorMod, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("Escravo recebe o vaor (%d) é envia o valor modificado (%d) para o mestre ", valorIncial, valorMod);
		fflush(stdout);
	}



	MPI_Finalize();
	return 0;
}

