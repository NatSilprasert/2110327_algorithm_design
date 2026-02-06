#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll mod_expo(ll x, ll n, ll k) {
    if (n == 0) {
        return 1 % k;
    } 

    ll tmp = mod_expo(x, n/2, k);
    tmp = (tmp * tmp) % k;

    if (n % 2 == 1) {
        tmp = (tmp * x) % k;
    }
    
    return tmp;
}

int main() {
    int x, n, k;
    cin >> x >> n >> k;

    cout << mod_expo(x, n, k);

    return 0;
}