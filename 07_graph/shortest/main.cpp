#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
struct Node {
    int r, c, dist;
};

int main() {
    int R, C;
    cin >> R >> C;

    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
        cin >> grid[i];
    }

    vector<vector<bool>> visited(R, vector<bool>(C, false));
    visited[0][0] = true;                                    

    queue<Node> q;
    q.push({0, 0, 0});

    int dr[] = {1, -1, 0, 0}; // การเคลื่อนที่ในแนวตั้ง (ลง, ขึ้น)
    int dc[] = {0, 0, 1, -1}; // การเคลื่อนที่ในแนวนอน (ขวา, ซ้าย)

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.r == R - 1 && current.c == C - 1) {
            cout << current.dist << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C && !visited[nr][nc] && grid[nr][nc] == '.') {
                visited[nr][nc] = true;
                q.push({nr, nc, current.dist + 1});
            }
        }
    }

    cout << "-1" << endl;
    return 0;
}