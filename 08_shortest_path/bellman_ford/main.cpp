#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e, s;
    cin >> n >> e >> s;

    vector<Edge> edges;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<long long> dist(n, INF);
    dist[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (const Edge &edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.w;
            }
        }
    }

    bool hasNegCycle = false;
    for (const Edge &edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.w) {
            hasNegCycle = true;
            break;
        }
    }

    if (hasNegCycle) {
        cout << -1 << endl;
    }
    else {
        for (int i = 0; i < n; i++) {
            if (dist[i] >= INF / 2) { 
                // ถ้าค่าเข้าใกล้ INF แสดงว่าไปไม่ถึง
                cout << "INF" << " ";
            }
            else {
                cout << dist[i] << " ";
            }
        }
    }

    return 0;
}