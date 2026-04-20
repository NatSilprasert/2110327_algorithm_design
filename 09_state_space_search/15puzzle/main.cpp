#include <iostream>
#include <vector>

using namespace std;

int result = 1e9;
vector<vector<int>> p(4, vector<int>(4));
int goalX[16], goalY[16];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int limit;
bool solved;
int next_limit;

int getHeuristic(const vector<vector<int>> &p) {
    int distance = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int val = p[i][j];
            if (val != 0) {
                distance += abs(i - goalX[val]) + abs(j - goalY[val]);
            }
        }
    }
    return distance;
}

void solve(int rowIdx, int colIdx, int prevMove, int moveCount) {
    int h = getHeuristic(p);
    int f = moveCount + h;

    if (f > limit) {
        next_limit = min(next_limit, f);
        return;
    }

    if (h == 0) {
        result = moveCount;
        solved = true;
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (prevMove != -1 && (i ^ 1) == prevMove) continue;

        int nr = rowIdx + dx[i];
        int nc = colIdx + dy[i];

        if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4) {
            swap(p[rowIdx][colIdx], p[nr][nc]);
            solve(nr, nc, i, moveCount + 1);
            if (solved) return;
            swap(p[rowIdx][colIdx], p[nr][nc]); // backtrack
        }
    }
}

int main() {
    int rowIdx, colIdx, c = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x;
            cin >> x;
            p[i][j] = x;
            if (x == 0) {
                rowIdx = i; 
                colIdx = j;
            }
        }
    }

    for (int i = 0; i < 15; i++) {
        goalX[i + 1] = i / 4;
        goalY[i + 1] = i % 4;
    }

    limit = getHeuristic(p);
    while (!solved && limit < 100) {
        next_limit = 1e9;
        solve(rowIdx, colIdx, -1, 0);
        if (!solved) {
            limit = next_limit;
        }
    }

    cout << result;

    return 0;
}