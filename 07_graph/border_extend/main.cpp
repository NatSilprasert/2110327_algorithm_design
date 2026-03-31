#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int row, col, count;
};

int main() {
    int r, c, k;
    cin >> r >> c >> k;

    vector<vector<int>> v(r, vector<int>(c));
    queue<Node> q;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> v[i][j];
            if (v[i][j] == 1) q.push({i, j, 0});
        }
    }

    vector<int> row_moves = {1, -1, 0, 0};
    vector<int> col_moves = {0, 0, 1, -1};

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        if (node.count == k) continue;

        int curr_row = node.row;
        int curr_col = node.col;

        for (int i = 0; i < 4; i++) {
            int next_row = curr_row + row_moves[i];
            int next_col = curr_col + col_moves[i];
            
            if (next_row < 0 || next_row >= r || next_col < 0 || next_col >= c) {
                continue;
            }
            if (v[next_row][next_col] != 0) {
                continue;
            }

            v[next_row][next_col] = 2;
            q.push({next_row, next_col, node.count + 1});
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}