#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

// initial dist = distance between u and v;
void foyd_warshall(int n, vector<vector<int>> &dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}