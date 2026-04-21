#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 80%

int n, m;
int K[15];
int used[15];
vector<vector<pair<int, int>>> nodes;
bool check = false;

vector<int> prefixWeightSum;
vector<int> allWeights;

void solve(int idx, int remain, int usedCount) {
    if (check) return;
    if (remain < 0) return;
    if (remain == 0) {
        check = true;
        return;
    }

    if (remain > prefixWeightSum[n - usedCount]) return;

    for (auto &[next, weight] : nodes[idx]) {
        if (!used[next]) {
            used[next] = 1;
            solve(next, remain - weight, usedCount + 1);
            used[next] = 0;
        }
    }
}

int main() {
    cin >> n >> m;
    nodes.resize(n + 1);
    for (int i = 1; i <= 8; i++) cin >> K[i];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (nodes[u].empty()) nodes[u] = {{v, w}};
        else nodes[u].push_back({v, w});
        if (nodes[v].empty()) nodes[v] = {{u, w}};
        else nodes[v].push_back({u, w});

        allWeights.push_back(w);
    }

    sort(allWeights.begin(), allWeights.end(), greater<int>());

    int L = allWeights.size();
    prefixWeightSum.resize(L + 1);
    prefixWeightSum[0] = 0;
    for (int i = 1; i <= L; i++) {
        prefixWeightSum[i] = prefixWeightSum[i - 1] + allWeights[i - 1];
    }

    for (int i = 1; i <= n; ++i) {
        sort(nodes[i].begin(), nodes[i].end(), [](auto &a, auto &b) {
                 return a.second > b.second;
             });
    }

    for (int i = 1; i <= 8; i++) {
        int k = K[i];
        check = false;
        fill(used, used + 15, 0);

        for (int i = 1; i <= n; i++) {
            if (!check) {
                used[i] = 1;
                solve(i, k, 1);
                used[i] = 0;
            }
        }
        if (check) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}