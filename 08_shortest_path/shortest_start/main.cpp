#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
};

const int INF = 1e9;

int n, m, k, target;
vector<int> start_nodes;
vector<Edge> edges;
vector<int> dist;

void bellman_ford(int s) {
    dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (const Edge &edge : edges) {
            if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  
    cin >> n >> m >> k >> target;

    start_nodes.resize(k);
    dist.assign(n, INF);
    edges.resize(m);

    for (int i = 0; i < k; i++) cin >> start_nodes[i];
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        // Reverse the edge direction so we can run Bellman-Ford from the target
        // and compute distances from all start nodes to the target.
        edges[i] = {b, a, w};
    }

    bellman_ford(target);

    int shortest_cost = INF;
    for (int start : start_nodes) {
        shortest_cost = min(shortest_cost, dist[start]);
    }

    cout << shortest_cost;

    return 0;
}