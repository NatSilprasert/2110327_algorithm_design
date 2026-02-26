#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

string s1, s2;
vector<vector<ll>> memo;

ll solve(int i, int j) {
    // case 1
    if (i == 0 || j == 0) return 0;
    
    if (memo[i][j] != -1) return memo[i][j];
    
    // case 2
    if (s1[i - 1] == s2[j - 1]) {
        return memo[i][j] = 1 + solve(i - 1, j - 1);
    }
    
    // case 3
    return memo[i][j] = max(solve(i - 1, j), solve(i, j - 1));
}

int main() {
    cin >> s1 >> s2;

    int n = s1.size();
    int m = s2.size();

    memo.assign(n + 1, vector<ll>(m + 1, -1));

    cout << solve(n, m) << endl;

    return 0;
}