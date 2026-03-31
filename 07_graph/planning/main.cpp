#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> adj[1005];
vector<int> in_deg(1005, 0);
queue<int> q;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;

        if (m == 0) {
            q.push(i);
            continue;
        }
        
        for (int j = 0; j < m; j++) {
            int pre;
            cin >> pre;
            adj[pre].push_back(i);
            in_deg[i]++;
        }
    }

    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        for (int x : adj[node]) {
            in_deg[x]--;
            if (in_deg[x] == 0) q.push(x);
        }
    }

    for (int x : result) cout << x << " ";

    return 0;
}