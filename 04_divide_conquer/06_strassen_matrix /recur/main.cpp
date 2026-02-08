#include <iostream>
#include <vector>

using namespace std;

void H(vector<vector<int>> &v, int a, int b, int startR, int endR, int startC, int endC, int op) {
    if (a == -1) return;

    for (int i = startR; i <= endR; i++) {
        for (int j = startC; j <= endC; j++) {
            v[i][j] += op;
        }
    }

    int mR = (startR + endR) / 2;
    int mC = (startC + endC) / 2;
    
    H(v, a - 1, b, startR, mR, startC, mC, 0);      // topLeft
    H(v, a - 1, b, startR, mR, mC + 1, endC, -1);   // topRight
    H(v, a - 1, b, mR + 1, endR, startC, mC, 1);    // bottomLeft
    H(v, a - 1, b, mR + 1, endR, mC + 1, endC, 0);  // bottomRight
}

int main() {
    int a, b;
    cin >> a >> b;

    int size = pow(2, a);
    vector<vector<int>> v(size, vector<int>(size));
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            v[i][j] = b;
        }
    }

    H(v, a, b, 0, size - 1, 0, size - 1, 0);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}