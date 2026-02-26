#include <iostream>
#include <vector>

using namespace std;

// 1. Top Down

vector<vector<long long>> dp;

long long cnk(int n, int k) {
    if (k == 0 || n == k) return 1;

    if (dp[n][k] != -1) return dp[n][k];

    return dp[n][k] = cnk(n - 1, k - 1) + cnk(n - 1, k);
}

int main() {
    int n, k;
    cin >> n >> k;

    dp.assign(n + 1, vector<long long>(k + 1, -1));
    
    cout << cnk(n, k);

    return 0;
}