#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> v;
vector<vector<int>> mem;

int solve(int start, int stop) {
    if (start >= stop) return 0;
    if (mem[start][stop] != -1) return mem[start][stop];

    int cut_left_left = max(v[start], v[start + 1]) + solve(start + 2, stop);
    int cut_right_right = max(v[stop], v[stop - 1]) + solve(start, stop - 2);
    int cut_left_right = max(v[start], v[stop]) + solve(start + 1, stop - 1);

    return mem[start][stop] = max({cut_left_left, cut_right_right, cut_left_right});
}

int main() {
    int n;
    cin >> n;
    v.resize(n);
    mem.assign(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << solve(0, n - 1);

    return 0;
}