#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[10005];
bool visited[10005]; 

void dfs(int node) {
    visited[node] = true;
    for (int x : adj[node]) {
        if (!visited[x]) {
            dfs(x);
        }
    }
}

int main() {
    int v, e;
    cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int component_count = 0;
    for (int i = 1; i <= v; i++) {
        if (!visited[i]) {
            dfs(i);
            component_count++;
        }
    }

    cout << component_count;

    return 0;
}