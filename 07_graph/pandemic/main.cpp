#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int row;
    int col;
    int day;
};

vector<vector<int>> v;
vector<vector<int>> visited;
queue<Node> q;

int main() {
    int r, c, T;
    cin >> r >> c >> T;

    v.assign(r, vector<int>(c));
    visited.assign(r, vector<int>(c, 0));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> v[i][j];
            if (v[i][j] == 1) q.push({i, j, 0});
            if (v[i][j] != 0) visited[i][j] = 1;
        }
    }

    vector<int> row_moves = {1, -1, 0, 0};
    vector<int> col_moves = {0, 0, 1, -1};

    int count = q.size();
    while (!q.empty()) {
        Node target = q.front();
        q.pop();

        if (target.day == T) continue;

        for (int i = 0; i < 4; i++) {
            int row_idx = target.row + row_moves[i];
            int col_idx = target.col + col_moves[i];

            if (row_idx < 0 || row_idx >= r || col_idx < 0 || col_idx >= c) continue;
            if (visited[row_idx][col_idx] == 1) continue; 

            visited[row_idx][col_idx] = 1;
            q.push({row_idx, col_idx, target.day + 1});
            count++;
        }
    }

    cout << count;

    return 0;
}