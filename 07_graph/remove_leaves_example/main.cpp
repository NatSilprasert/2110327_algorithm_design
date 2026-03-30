#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> adj[100005];
vector<bool> visited(100005, false);
vector<int> deg(100005, 0);
vector<bool> removed(100005, false);

int main() {
    int v, e;
    cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a); 
        deg[a]++;
        deg[b]++;
    }

    queue<int> leaves;
    for (int i = 0; i < v; i++) {
        if (deg[i] == 1) leaves.push(i);
    }

    while (!leaves.empty()) {
        int node = leaves.front(); 
        leaves.pop();
        removed[node] = true;

        for (int x : adj[node]) {
            if (!removed[node]) {
                deg[x]--;
                if (deg[x] == 1) leaves.push(x);
            }
        }
    }

    return 0;
}