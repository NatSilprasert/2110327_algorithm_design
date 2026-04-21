#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<vector<pair<int, int>>> adj; // {to, weight}

const int INF = 1e9;

vector<int> dijkstra(int n, int start) {
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({dist[start], start});
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [to, weight] : adj[u]) {
            if (weight + d < dist[to]) {
                dist[to] = weight + d;
                pq.push({dist[to], d});
            }
        }
    }

    return dist;
}