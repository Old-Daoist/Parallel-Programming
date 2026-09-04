#include <iostream>
using namespace std;

int main() {
    const int N = 4;

    int A[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int X[N] = {3, 4, 5, 6};

    int Y[N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Y[i] += A[i][j] * X[j];
        }
    }

    cout << "Result:\n";
    for (int i = 0; i < N; i++) {
        cout << Y[i] << endl;
    }

    return 0;
}