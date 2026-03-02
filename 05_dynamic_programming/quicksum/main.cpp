#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> v, p;
int n, m, k;

int main() {
    cin >> n >> m >> k;
    v.assign(n, vector<int>(m));
    p.assign(n, vector<int>(m));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    // build prefix sum
    p[0][0] = v[0][0];
    for (int i = 1; i < n; i++) {
        p[i][0] = p[i - 1][0] + v[i][0];
    }
    for (int j = 1; j < m; j++) {
        p[0][j] = p[0][j - 1] + v[0][j];
        for (int i = 1; i < n; i++) {
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + v[i][j];
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         cout << p[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < k; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int total = p[r2][c2];
        if (r1 > 0) total -= p[r1 - 1][c2];
        if (c1 > 0) total -= p[r2][c1 - 1];
        if (r1 > 0 && c1 > 0) total += p[r1 - 1][c1 - 1];   
        cout << total << endl;
    }

    return 0;
}