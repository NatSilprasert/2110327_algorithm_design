#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

vector<vector<ll>> memo;
vector<int> weight, value;
int n, W;

ll solve(int i, int W) {
    if (W == 0 || i == n) return 0;

    if (memo[i][W] != -1) return memo[i][W];

    // not take
    ll not_take = solve(i + 1, W);

    // take
    ll take = 0;
    if (weight[i] <= W) {
        take = value[i] + solve(i + 1, W - weight[i]);
    }

    return memo[i][W] = max(not_take, take);
}

int main() {
    cin >> n >> W;

    weight.resize(n);
    value.resize(n);
    memo.assign(n, vector<ll>(W + 1, -1));

    for (int i = 0; i < n; i++) {
        cin >> weight[i];
        cin >> value[i];
    }

    cout << solve(0, W);

    return 0;
}