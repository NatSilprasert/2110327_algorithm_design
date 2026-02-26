#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    int n, W;
    cin >> n >> W;

    vector<int> weight(n), value(n);

    for (int i = 0; i < n; i++) cin >> weight[i] >> value[i];

    vector<vector<ll>> dp(n + 1, vector<ll>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            dp[i][w] = dp[i - 1][w]; // ไม่เลือก

            if (w >= weight[i - 1]) {
                dp[i][w] = max(
                    dp[i][w],
                    value[i - 1] + dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    cout << dp[n][W] << endl;

    return 0;
}