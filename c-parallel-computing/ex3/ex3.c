#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int
main(int argc, char *argv[])
{
        int nproc, rank, root = 0;
        int rc;

        if ((rc = MPI_Init(&argc, &argv)) != 0) {
                fprintf(stderr, "%s: cannot initiliaze MPI.\n", argv[0]);
                MPI_Abort(MPI_COMM_WORLD, rc);
        }
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        MPI_Finalize();

        return 0;
}
