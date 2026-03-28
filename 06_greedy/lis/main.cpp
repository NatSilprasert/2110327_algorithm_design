#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;
vector<int> v;

int solve(int idx, int prev_idx) {
    if (idx < 0) return 0;

    if (memo[idx][prev_idx + 1] != -1) return memo[idx][prev_idx + 1];

    int take = 0;
    if (prev_idx == -1 || v[idx] < v[prev_idx]) {
        take = 1 + solve(idx - 1, idx);
    }
    int skip = solve(idx - 1, prev_idx);

    return memo[idx][prev_idx + 1] = max(take, skip);
}

int main() {
    int n;
    cin >> n;

    v.resize(n);
    memo.assign(n, vector<int>(n + 1, -1));
    
    for (int i = 0; i < n; i++) cin >> v[i];

    cout << solve(n - 1, -1);

    return 0;
}