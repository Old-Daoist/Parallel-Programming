#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int ROWS = 4;
    const int COLS = 8;

    int A[ROWS * COLS] = {
        1,  2,  3,  4,  5,  6,  7,  8,
        9,  10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32
    };

    int X[COLS] = {
        2, 4, 6, 8, 3, 9, 4, 5
    };

    int local_A[COLS];

    int local_Y;

    int Y[ROWS];

    MPI_Scatter(
        A,
        COLS,
        MPI_INT,
        local_A,
        COLS,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    MPI_Bcast(
        X,
        COLS,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );
    local_Y = 0;

    for (int j = 0; j < COLS; j++) {

        local_Y += local_A[j] * X[j];

    }

    MPI_Gather(
        &local_Y,
        1,
        MPI_INT,
        Y,
        1,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {

        cout << "Result Y:\n";

        for (int i = 0; i < ROWS; i++) {

            cout << Y[i] << endl;

        }
    }

    MPI_Finalize();

    return 0;
}