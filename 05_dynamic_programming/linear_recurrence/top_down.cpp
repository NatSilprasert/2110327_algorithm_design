#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll MOD = 32717;

ll k, n;
vector<ll> c;
vector<ll> a;
vector<ll> memo;

ll solve(ll x) {
    if (x < k) return a[x];

    if (memo[x] != -1) return memo[x];

    ll result = 0;
    for (ll j = 0; j < k; j++) {
        result = (result + c[j] * solve(x - j - 1)) % MOD;
    }

    memo[x] = result;

    return result;
}

int main() {
    cin >> k >> n;

    c.resize(k);
    a.resize(k);

    for (ll i = 0; i < k; i++) {
        cin >> c[i];
        c[i] = ((c[i] % MOD) + MOD) % MOD; // prevent negative value
    }

    for (ll i = 0; i < k; i++) {
        cin >> a[i];
        a[i] = ((a[i] % MOD) + MOD) % MOD; // prevent negative value
    }

    memo.assign(n + 1, 0);

    cout << solve(n) << endl;

    return 0;
}