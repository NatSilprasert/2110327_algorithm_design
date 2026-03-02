#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> v;
vector<int> maxV;

int main() {
    cin >> n;
    v.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
    }

    // row
    for (int i = 0; i < n; i++) {
        int curSum = v[i][0];
        int maxSum = curSum;
        for (int j = 1; j < n; j++) {
            if (i + j >= n) break; 
            curSum = max(curSum + v[i + j][j], v[i + j][j]);
            maxSum = max(curSum, maxSum);
        }
        maxV.push_back(maxSum);
    }
    // col
    for (int i = 0; i < n; i++) {
        int curSum = v[0][i];
        int maxSum = curSum;
        for (int j = 1; j < n; j++) {
            if (i + j >= n) break; 
            curSum = max(curSum + v[j][i + j], v[j][i + j]);
            maxSum = max(curSum, maxSum);
        }
        maxV.push_back(maxSum);
    }

    // for (int e : maxV) cout << e << endl;

    sort(maxV.begin(), maxV.end());
    cout << maxV.back();

    return 0;
}