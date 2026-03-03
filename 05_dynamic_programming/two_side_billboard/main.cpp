#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, w, k;
vector<int> l;
vector<int> r;
vector<vector<int>> mem1;
vector<vector<vector<int>>> mem2;

int solve2(int s, int op, int count) {
    if (count < 0) return -1e9;
    if (s < 0) return (count == 0 ? 0 : -1e9);
    if (mem2[s][op][count] != -1) return mem2[s][op][count];

    int pick_current;
    int skip_current = solve2(s - 1, op, count);

    int pick_left = l[s] + solve2(s - w - 1, 1, count - 1);
    int pick_right = r[s] + solve2(s - w - 1, 0, count - 1);

    if (op == 0) pick_current = pick_left;
    else if (op == 1) pick_current = pick_right;
    else pick_current = max(pick_left, pick_right);

    return mem2[s][op][count] = max(pick_current, skip_current);
}

int solve1(int s, int op) {
    if (s < 0) return 0;
    if (mem1[s][op] != -1) return mem1[s][op]; 

    int pick_current;
    int skip_current = solve1(s - 1, op);

    int pick_left = l[s] + solve1(s - w - 1, 1);
    int pick_right = r[s] + solve1(s - w - 1, 0);
    
    if (op == 0) pick_current = pick_left;
    else if (op == 1) pick_current = pick_right;
    else pick_current = max(pick_left, pick_right);

    return mem1[s][op] = max(pick_current, skip_current);
}

int main() {
    cin >> n >> w >> k;
    l.resize(n);
    r.resize(n);
    if (n ==k) mem1.assign(n, vector<int>(3, -1));
    else {
        vector<vector<int>> tmp;
        tmp.assign(3, vector<int>(k + 1, -1));
        mem2.assign(n, tmp);
    }

    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    int ans = n == k ? solve1(n - 1, 2) : solve2(n - 1, 2, k);
    cout << ans;

    return 0;
}