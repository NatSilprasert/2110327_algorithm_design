#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> c(n + 1);
    vector<int> dp(n);

    for (int i = 0; i < n; i++) {
        cin >> c[i];    
    }
    
    dp[0] = 0;
    dp[1] = c[0];
    for (int i = 2; i <= n; i++) {
        int take_current = dp[i - 2] + c[i - 1];
        int skip_current = dp[i - 1];
        dp[i] = max(take_current, skip_current);
    }

    cout << dp[n];

    return 0;
}