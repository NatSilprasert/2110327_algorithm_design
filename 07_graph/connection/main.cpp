#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, e, k;
vector<int> adj[1005];

int countDeg(int start) {
    vector<int> depth(n, -1);
    queue<int> q;
    depth[start] = 0;
    q.push(start);

    int count = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (depth[node] > k) continue;
        count++;

        for (int x : adj[node]) {
            if (depth[x] == -1) {
                depth[x] = depth[node] + 1;
                if (depth[x] <= k) {
                    q.push(x);
                }
            }
        }
    }

    return count;
}

int main() {
    cin >> n >> e >> k;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int maxDeg = 0;

    for (int i = 0; i < n; i++) {
        int currDeg = countDeg(i);
        maxDeg = max(maxDeg, currDeg);
    }

    cout << maxDeg;

    return 0;
}