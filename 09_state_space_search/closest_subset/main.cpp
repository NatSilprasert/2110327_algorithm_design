#include <iostream>
#include <vector>

using namespace std;

// this code only get 60%, I gave up

int n, m, k, ans = 1e9;
int A[105];

void solve(int idx, int cost, int count) {
    if (count == m) {
        int diff = abs(cost - k);
        ans = min(ans, diff);
        return;
    }

    if (idx >= n)
        return;

    // take current
    solve(idx + 1, cost + A[idx], count + 1);
    // skip current
    if (n - idx - 1 >= m - count) {
        solve(idx + 1, cost, count);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> A[i];

    solve(0, 0, 0);

    cout << ans;

    return 0;
}