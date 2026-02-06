#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
    long long mat[2][2];
};

Matrix matrix_multiply(Matrix A, Matrix B, int k) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C.mat[i][j] = 0;
            for (int l = 0; l < 2; l++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][l] * B.mat[l][j]) % k;
            }
        }
    }
    return C;
}

Matrix matrix_mod(Matrix A, int k) {
    A.mat[0][0] %= k; A.mat[0][1] %= k;
    A.mat[1][0] %= k; A.mat[1][1] %= k;
    return A;
}

Matrix power(Matrix A, int n, int k) {
    if (n == 0) {
        Matrix I;
        I.mat[0][0] = 1; I.mat[0][1] = 0;
        I.mat[1][0] = 0; I.mat[1][1] = 1;
        return I;
    }

    Matrix B; 
    B.mat[0][0] = 1; B.mat[0][1] = 0;
    B.mat[1][0] = 0; B.mat[1][1] = 1;

    Matrix tmp = power(A, n/2, k);
    tmp = matrix_multiply(tmp, tmp, k); 
    
    if (n % 2 == 1) {
        tmp = matrix_multiply(tmp, A, k);
    }
    
    return tmp = matrix_mod(tmp, k);
}


int main() {
    int n, k;
    cin >> n >> k;

    Matrix M;
    cin >> M.mat[0][0] >> M.mat[0][1] >> M.mat[1][0] >> M.mat[1][1];
    
    M = power(M, n, k);
    cout << M.mat[0][0] << " " << M.mat[0][1] << " " << M.mat[1][0] << " " << M.mat[1][1];

    return 0;
}