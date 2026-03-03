#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v;
vector<vector<int>> dp;

int main() {
    cin >> n >> m;
    v.resize(n + 1);
    dp.assign(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) cin >> v[i];

    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 1; i <= m; i++) dp[0][i] = 10000000;
    
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (j < v[i]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - v[i]] + 1);
            }
        }
    }

    cout << dp[n][m];

    return 0;
}