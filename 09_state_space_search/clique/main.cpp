#include <iostream>
#include <vector>

using namespace std;

int n, result = 0;
int B[55];
int F[55][55];
int used[55];
int totalSumLeft[55];

bool isValid(int x) {
    for (int i = 0; i < x; i++) {
        if (used[i] && !F[i][x]) return false;
    }
    return true;
}

void solve(int idx, int cost) {
    if (idx >= n) {
        result = max(cost, result);
        return;
    }

    if (totalSumLeft[idx] + cost < result) return;

    // take current (if valid)
    if (isValid(idx)) {
        used[idx] = 1;
        solve(idx + 1, cost + B[idx]);
    }
    // skip current
    used[idx] = 0;
    solve(idx + 1, cost);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> B[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> F[i][j];
        }
    }

    totalSumLeft[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        totalSumLeft[i] = totalSumLeft[i + 1] + B[i];
    }

    solve(0, 0);

    cout << result;

    return 0;
}