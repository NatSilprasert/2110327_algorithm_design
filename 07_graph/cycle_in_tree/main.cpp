#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[100005];
int visited[100005];
int depth[100005];

int dfs(int node, int parent) {
    visited[node] = 1;
    for (int x : adj[node]) {
        if (!visited[x]) {
            depth[x] = depth[node] + 1;
            int result = dfs(x, node);
            if (result != -1) return result;
        }
        else if (parent != x) {
            return depth[node] - depth[x] + 1;  
        }
    }
    return -1;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            depth[i] = 0;
            int result = dfs(i, -1);
            if (result != -1) {
                cout << result;
                return 0;
            }
        }
    }

    return 0;
}