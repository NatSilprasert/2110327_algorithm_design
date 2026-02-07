#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

ll p, k, A, B;

ll get_avenger(vector<ll> &v, ll start, ll stop) {
    auto it1 = lower_bound(v.begin(), v.end(), start);
    auto it2 = upper_bound(v.begin(), v.end(), stop);
    return distance(it1, it2);
}

ll split(vector<ll> &v, ll start, ll stop) {
    
    ll numAvenger = get_avenger(v, start, stop);
    if (numAvenger == 0) return A;

    ll tmpPower = B * (stop - start + 1) * numAvenger;

    if (start >= stop) {
        return B * numAvenger;
    }

    ll m = (start + stop) / 2;
    return min(split(v, start, m) + split(v, m + 1, stop), tmpPower);

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> p >> k >> A >> B;

    ll length = pow(2, p);
    vector<ll> v(k);

    for (ll i = 0; i < k; i++) {
        int x;
        cin >> x;
        v[i] = x - 1;
    }

    sort(v.begin(), v.end());

    cout << split(v, 0, length - 1);

    return 0;
}