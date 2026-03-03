#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> c;
vector<int> mem;

int solve(int s) {
    if (s < 0) return 0;
    if (mem[s] != -1) return mem[s];

    int take_current = c[s] + solve(s - 3);
    int skip_current = solve(s - 1);

    return mem[s] = max(take_current, skip_current);
}

int main() {
    cin >> n;
    c.resize(n);
    mem.assign(n, -1);

    for (int i = 0; i < n; i++) {
      cin >> c[i];
    }

    cout << solve(n - 1);

    return 0;
}