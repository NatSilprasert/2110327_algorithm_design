#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

// get sum A[a..b] in O(1)
ll get_sum(const vector<ll> &S, int a, int b) {
    if (a == 0) return S[b];
    return S[b] - S[a - 1];
}

// Maximum Subarray Sum using Divide & Conquer + Prefix Sum
ll mss(const vector<ll> &A,
              const vector<ll> &S,
              int start, int stop)
{
    // base case
    if (start == stop) {
        return A[start];
    }

    int m = (start + stop) / 2;

    // left and right
    ll r1 = mss(A, S, start, m);
    ll r2 = mss(A, S, m + 1, stop);

    // find max of B[start..m][m]
    ll max_sum_left = A[m];
    for (int i = start; i <= m - 1; i++) {
        max_sum_left = max(max_sum_left, get_sum(S, i, m));
    }

    // find max of B[m+1..stop][stop]
    ll max_sum_right = A[m + 1];
    for (int j = m + 2; j <= stop; j++) {
        max_sum_right = max(max_sum_right, get_sum(S, m + 1, j));
    }

    ll r3 = max_sum_left + max_sum_right;

    return max({r1, r2, r3});
}

int main() {
    vector<ll> A = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = A.size();

    // build prefix sum
    vector<ll> S(n);
    S[0] = A[0];
    for (int i = 1; i < n; i++) {
        S[i] = S[i - 1] + A[i];
    }

    cout << mss(A, S, 0, n - 1) << endl; // 6

    return 0;
}