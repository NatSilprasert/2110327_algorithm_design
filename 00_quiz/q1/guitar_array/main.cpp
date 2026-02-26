#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

typedef long long ll;

ll solve(vector<ll> &v, ll start, ll stop, ll x)
{
    if (start == stop)
    {
        return x == v[start] ? 1 : 0;
    }

    ll m = (start + stop) / 2;

    bool isLeft = true;
    bool isRight = true;

    // check left
    for (ll i = start; i <= m; i++)
    {
        if (v[i] != x)
            isLeft = false;
    }

    // check right
    for (ll i = m + 1; i <= stop; i++)
    {
        if (v[i] != x)
            isRight = false;
    }

    if (isLeft && !isRight)
        return solve(v, m + 1, stop, x + 1);
    else if (isRight && !isLeft)
        return solve(v, start, m, x + 1);
    else
        return 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    ll n;
    cin >> n;

    for (ll j = 1; j <= n; j++)
    {
        // cout << "round: " << j << endl;
        ll k, x;
        cin >> k >> x;

        ll size = pow(2, k);
        vector<ll> v(size);

        for (ll i = 0; i < size; i++)
        {
            ll input;
            cin >> input;
            v[i] = input;
        }

        ll result = solve(v, 0, size - 1, x);

        // cout << result;
        if (result == 1)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}