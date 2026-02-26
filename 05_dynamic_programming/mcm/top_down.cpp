#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long ll;

vector<vector<ll>> memo;
vector<int> p;

ll solve(int i, int j) {
    if (i == j) return 0; 

    if (memo[i][j] != -1) return memo[i][j];

    ll ans = LLONG_MAX;
    for (int k = i; k < j; k++) {
        ll cost = solve(i, k) + solve(k + 1, j) + (1LL * p[i - 1] * p[k] * p[j]);
        ans = min(ans, cost);
    }

    memo[i][j] = ans;
    return ans;
}

int main() {
    int n; 
    cin >> n;

    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    memo.assign(n, vector<ll>(n, -1));

    cout << solve(1, n - 1) << endl;

    return 0;
}