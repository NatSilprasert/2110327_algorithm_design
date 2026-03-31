#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;

    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = parent[root_j];
            return true;
        }
        return false;
    }

};

vector<Edge> edges;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int w;
            cin >> w;
            edges.push_back({i, j, w});
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu = DSU(n);
    int min_cost = 0;
    int edge_count = 0;

    for (auto edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            edge_count++;
            min_cost += edge.weight;
            if (edge_count == n - 1) break;
        }
    }

    cout << min_cost;

    return 0;
}