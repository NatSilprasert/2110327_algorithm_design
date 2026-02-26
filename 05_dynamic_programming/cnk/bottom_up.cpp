#include <iostream>
#include <vector>

using namespace std;

// 2. Bottom Up

int main() {
    int n, k;
    cin >> n >> k;

    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));

    for (int i = 0; i <= n; i++) {
        dp[i][i] = 1;
        dp[i][0] = 1;
    }

    for (int i = i; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }

    cout << dp[n][k];

    return 0;
}