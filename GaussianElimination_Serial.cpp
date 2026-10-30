#include <iostream>
using namespace std;

int main() {
    const int N = 6;

    double matrix[N][N + 1] = {
        {2,  1, -1,  1,  1, -1,  4},
        {1,  3,  1, -1,  2,  1, 22},
        {-1, 1,  4,  1, -1,  2, 24},
        {1, -1,  1,  5,  2, -1, 26},
        {2,  1, -1,  2,  4,  1, 35},
        {-1, 2,  1, -1,  1,  3, 25}
    };

    for (int pivot = 0; pivot < N; pivot++) {
        if (matrix[pivot][pivot] == 0) {
            cout << "Cannot solve: a diagonal number is zero.\n";
            return 1;
        }

        for (int row = pivot + 1; row < N; row++) {
            double multiplier = matrix[row][pivot] / matrix[pivot][pivot];

            for (int column = pivot; column <= N; column++) {
                matrix[row][column] =
                    matrix[row][column] - multiplier * matrix[pivot][column];
            }
        }
    }

    double answer[N] = {};
    for (int row = N - 1; row >= 0; row--) {
        answer[row] = matrix[row][N];

        for (int column = row + 1; column < N; column++) {
            answer[row] = answer[row] - matrix[row][column] * answer[column];
        }

        answer[row] = answer[row] / matrix[row][row];
    }

    cout << "Solution:\n";
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << answer[i] << '\n';
    }

    return 0;
}
