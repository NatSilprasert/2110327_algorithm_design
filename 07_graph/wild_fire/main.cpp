#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> b(10005);
vector<int> date(10005);

vector<int> adj[10005];
vector<bool> visited(10005, false);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    int beauty = 0;

    // initialize 
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        beauty += b[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> date[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    // start
    for (int i = 0; i < k; i++) {
        int node = date[i];
        if (visited[node]) {
            cout << beauty << " ";
            continue;
        }

        queue<int> q;
        q.push(node);
        visited[node] = true;
        while (!q.empty()) {
            int targetNode = q.front();
            q.pop();

            beauty -= b[targetNode];

            for (int x : adj[targetNode]) {
                if (!visited[x]) {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }

        cout << beauty << " ";
    }

    return 0;
}