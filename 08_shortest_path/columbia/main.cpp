#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct Node {
    int r, c, cost;
    bool operator>(const Node &other) const {
        return cost > other.cost;
    }
};

int main() {
    int r, c;
    cin >> r >> c;

    vector<vector<int>> v(r, vector<int>(c));
    vector<vector<int>> dist(r, vector<int>(c, INF));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> v[i][j];
        }
    }

    vector<int> row_moves = {1, -1, 0, 0};
    vector<int> col_moves = {0, 0, 1, -1};


    // Dijkstra's Algorithm
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.cost > dist[curr.r][curr.c]) continue;

        for (int i = 0; i < 4; i++) {
            int next_row = curr.r + row_moves[i];
            int next_col = curr.c + col_moves[i];

            if (next_row < 0 || next_row >= r || next_col < 0 || next_col >= c) {
                continue;
            }
            
            int new_cost = dist[curr.r][curr.c] + v[next_row][next_col];
            
            if (dist[next_row][next_col] < new_cost) {
                continue;
            }

            dist[next_row][next_col] = new_cost;
            pq.push({next_row, next_col, new_cost});
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}