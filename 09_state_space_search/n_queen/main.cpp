#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int n, result = 0;
int q[20], used[20];

bool check(int depth) {
    for (int i = 0; i < depth; i++) {
        if (abs(i - depth) == abs(q[i] - q[depth])) return false;
    }
    return true;
}

void solve(int row_idx) {
    if (row_idx == n) {
        result++;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        q[row_idx] = i;
        used[i] = 1;
        if (check(row_idx)) solve(row_idx + 1);
        used[i] = 0;
    }
}

int main() {
    cin >> n;
    solve(0);
    cout << result;
    return 0;
}