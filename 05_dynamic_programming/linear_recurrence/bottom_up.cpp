#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll MOD = 32717;

int main() {
    ll k, n;
    cin >> k >> n;

    vector<ll> c(k);
    vector<ll> a(k);
    vector<ll> dp(n + 1, 0);

    for (ll i = 0; i < k; i++) {
        cin >> c[i];
        c[i] = ((c[i] % MOD) + MOD) % MOD; // prevent negative value
    }

    for (ll i = 0; i < k; i++) {
        cin >> a[i];
        a[i] = ((a[i] % MOD) + MOD) % MOD; // prevent negative value
        dp[i] = a[i];
    }

    // if n < k return a[n]
    if (n < k) {
        cout << a[n] << endl;
        return 0;
    }

    // bottom-up
    for (ll i = k; i <= n; i++) {
        for (ll j = 0; j < k; j++) {
            dp[i] = (dp[i] + c[j] * dp[i - j - 1]) % MOD;
        }
    }

    cout << dp[n] << endl;

    return 0;
}