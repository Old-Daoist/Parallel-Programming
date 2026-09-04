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
    const int COLS_PER_PROC = 2;

    int A[ROWS][COLS] = {
        {1,  2,  3,  4,  5,  6,  7,  8},
        {9,  10, 11, 12, 13, 14, 15, 16},
        {17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32}
    };

    int X[COLS] = {2, 4, 6, 8, 3, 9, 4, 5};

    // Packed matrix for Scatter
    int packed_A[ROWS * COLS];

    // Each process receives 2 columns
    int local_A[ROWS * COLS_PER_PROC];

    // Each process receives 2 elements of X
    int local_X[COLS_PER_PROC];

    // Partial result
    int local_Y[ROWS] = {0};

    // Final result
    int Y[ROWS] = {0};

    if (rank == 0) {

        int index = 0;

        for (int p = 0; p < size; p++) {

            int start_col = p * COLS_PER_PROC;

            for (int i = 0; i < ROWS; i++) {

                for (int j = 0; j < COLS_PER_PROC; j++) {

                    packed_A[index++] =
                        A[i][start_col + j];
                }
            }
        }
    }

    MPI_Scatter(
        packed_A,
        ROWS * COLS_PER_PROC,
        MPI_INT,
        local_A,
        ROWS * COLS_PER_PROC,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );


    MPI_Scatter(
        X,
        COLS_PER_PROC,
        MPI_INT,
        local_X,
        COLS_PER_PROC,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    for (int i = 0; i < ROWS; i++) {

        for (int j = 0; j < COLS_PER_PROC; j++) {

            local_Y[i] +=
                local_A[i * COLS_PER_PROC + j]
                * local_X[j];
        }
    }

    MPI_Reduce(
        local_Y,
        Y,
        ROWS,
        MPI_INT,
        MPI_SUM,
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