#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int c[2005];
vector<int> adj[2005];
vector<int> deg_in(2005, 0);
vector<int> min_val(2005, 0);
vector<bool> visited(2005, false);

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> c[i];
        min_val[i] = c[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        deg_in[v]++;
    }

    vector<int> startNode;
    for (int i = 0; i < n; i++) {
        if (deg_in[i] == 0) startNode.push_back(i);
    }

    int currMax = 0;
    for (int i : startNode) {
        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int targetNode = q.front();
            q.pop();

            for (int x : adj[targetNode]) {
                min_val[x] = min(min_val[x], min_val[targetNode]);
                currMax    = max(currMax, c[x] - min_val[x]);
                deg_in[x]--;
                if (deg_in[x] == 0) q.push(x);
            }
        }
    }

    cout << currMax;

    return 0;
}