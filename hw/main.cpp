#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

int N;
vector<vector<int>> board;
vector<vector<int>> targetPat;
vector<vector<bool>> locked;
int er, ec;
string moves;

// How empty cell shifts for each direction index k
// k=0: empty up   (dr=-1) → cmd='D'   (tile above empty moves down)
// k=1: empty down (dr=+1) → cmd='U'   (tile below empty moves up)
// k=2: empty left (dc=-1) → cmd='R'   (tile left of empty moves right)
// k=3: empty right(dc=+1) → cmd='L'   (tile right of empty moves left)
int drs[] = {-1, 1, 0, 0};
int dcs[] = {0, 0, -1, 1};
char cmdChar[] = {'D', 'U', 'R', 'L'};

// ==================== IDA* (used only for N=5) ====================

// target positions per color, precomputed once
vector<vector<pair<int,int>>> tgtByColor;

// Min-cost assignment: assign tgt[0..m-1] to m of the n sources (DP on bitmask of sources)
// Returns minimum total Manhattan distance. n must be <= 15.
int minAssign(const vector<pair<int,int>>& tgt, const vector<pair<int,int>>& src) {
    int m = (int)tgt.size(), n = (int)src.size();
    if (m == 0) return 0;
    vector<int> dp(1 << n, INT_MAX / 2);
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] >= INT_MAX / 2) continue;
        int ti = __builtin_popcount(mask);
        if (ti >= m) continue;
        for (int si = 0; si < n; si++) {
            if (mask >> si & 1) continue;
            int d = abs(tgt[ti].first  - src[si].first) +
                    abs(tgt[ti].second - src[si].second);
            int nm = mask | (1 << si);
            if (dp[mask] + d < dp[nm]) dp[nm] = dp[mask] + d;
        }
    }
    int res = INT_MAX / 2;
    for (int mask = 0; mask < (1 << n); mask++)
        if (__builtin_popcount(mask) == m) res = min(res, dp[mask]);
    return res;
}

int heuristic(const vector<vector<int>>& b) {
    // collect board positions per color
    vector<vector<pair<int,int>>> src(N + 2);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (b[i][j] > 0) src[b[i][j]].push_back({i, j});
    int h = 0;
    for (int c = 1; c <= N + 1; c++)
        if (!tgtByColor[c].empty())
            h += minAssign(tgtByColor[c], src[c]);
    return h;
}

int idaLimit, idaNextLimit;
bool idaSolved;

void idaDFS(vector<vector<int>>& b, int r, int c, int prevDir, int g, string& path) {
    int h = heuristic(b);
    int f = g + h;
    if (f > idaLimit) { idaNextLimit = min(idaNextLimit, f); return; }
    if (h == 0) { idaSolved = true; return; }
    for (int k = 0; k < 4; k++) {
        if (prevDir != -1 && k == (prevDir ^ 1)) continue; // don't immediately undo
        int nr = r + drs[k], nc = c + dcs[k];
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
        swap(b[r][c], b[nr][nc]);
        path += cmdChar[k];
        idaDFS(b, nr, nc, k, g + 1, path);
        if (idaSolved) return;
        path.pop_back();
        swap(b[r][c], b[nr][nc]);
    }
}

// ==================== Greedy (used for N > 5) ====================

bool moveEmptyTo(int tr, int tc, int forbidR, int forbidC) {
    if (er == tr && ec == tc) return true;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    q.push({er, ec});
    dist[er][ec] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == tr && c == tc) break;
        for (int k = 0; k < 4; k++) {
            int nr = r + drs[k], nc = c + dcs[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (locked[nr][nc]) continue;
            if (nr == forbidR && nc == forbidC) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            parent[nr][nc] = {r, c};
            q.push({nr, nc});
        }
    }
    if (dist[tr][tc] == -1) return false;

    vector<pair<int, int>> path;
    int cr = tr, cc = tc;
    while (cr != er || cc != ec) {
        path.push_back({cr, cc});
        auto [pr, pc] = parent[cr][cc];
        cr = pr; cc = pc;
    }
    reverse(path.begin(), path.end());
    for (auto [r, c] : path) {
        int dr = r - er, dc = c - ec;
        char cmd;
        if (dr == 1) cmd = 'U';
        else if (dr == -1) cmd = 'D';
        else if (dc == 1) cmd = 'L';
        else cmd = 'R';
        moves += cmd;
        board[er][ec] = board[r][c];
        board[r][c] = -1;
        er = r; ec = c;
    }
    return true;
}

bool moveTile(int sr, int sc, int tr, int tc) {
    vector<vector<int>> tdist(N, vector<int>(N, -1));
    vector<vector<pair<int, int>>> tparent(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    q.push({sr, sc});
    tdist[sr][sc] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int nr = r + drs[k], nc = c + dcs[k];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (locked[nr][nc]) continue;
            if (tdist[nr][nc] != -1) continue;
            tdist[nr][nc] = tdist[r][c] + 1;
            tparent[nr][nc] = {r, c};
            q.push({nr, nc});
        }
    }
    if (tdist[tr][tc] == -1) return false;

    vector<pair<int, int>> path;
    int cr = tr, cc = tc;
    while (cr != sr || cc != sc) {
        path.push_back({cr, cc});
        auto [pr, pc] = tparent[cr][cc];
        cr = pr; cc = pc;
    }
    reverse(path.begin(), path.end());

    int cur_tr = sr, cur_tc = sc;
    for (auto [nr, nc] : path) {
        if (!moveEmptyTo(nr, nc, cur_tr, cur_tc)) return false;
        int tdr = nr - cur_tr, tdc = nc - cur_tc;
        char cmd;
        if (tdr == -1) cmd = 'U';
        else if (tdr == 1) cmd = 'D';
        else if (tdc == -1) cmd = 'L';
        else cmd = 'R';
        moves += cmd;
        board[nr][nc] = board[cur_tr][cur_tc];
        board[cur_tr][cur_tc] = -1;
        er = cur_tr; ec = cur_tc;
        cur_tr = nr; cur_tc = nc;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    board.assign(N, vector<int>(N));
    locked.assign(N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == -1) {
                er = i; ec = j;
            }
        }
    }
    int M = N - 2;
    targetPat.assign(M, vector<int>(M));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            cin >> targetPat[i][j];

    if (N == 5) {
        // IDA* with min-cost matching heuristic
        tgtByColor.assign(N + 2, {});
        for (int i = 0; i < M; i++)
            for (int j = 0; j < M; j++)
                tgtByColor[targetPat[i][j]].push_back({i + 1, j + 1});

        idaSolved = false;
        idaLimit = heuristic(board);
        string path;
        while (!idaSolved) {
            idaNextLimit = INT_MAX;
            idaDFS(board, er, ec, -1, 0, path);
            if (idaSolved) break;
            if (idaNextLimit == INT_MAX) break;
            idaLimit = idaNextLimit;
        }
        cout << path << "S" << endl;
    } else {
        // Greedy with best-candidate selection for larger N
        int candLimit = (N <= 9) ? 100 : (N <= 25 ? 8 : 3);
        for (int r = 1; r <= N - 2; r++) {
            for (int c = 1; c <= N - 2; c++) {
                int want = targetPat[r - 1][c - 1];
                if (board[r][c] == want) {
                    locked[r][c] = true;
                    continue;
                }
                vector<vector<int>> tdist(N, vector<int>(N, -1));
                queue<pair<int, int>> q;
                q.push({r, c});
                tdist[r][c] = 0;
                vector<pair<int, pair<int, int>>> cands;
                while (!q.empty()) {
                    auto [cr, cc] = q.front(); q.pop();
                    if (board[cr][cc] == want && !(cr == r && cc == c))
                        cands.push_back({tdist[cr][cc], {cr, cc}});
                    for (int k = 0; k < 4; k++) {
                        int nr = cr + drs[k], nc = cc + dcs[k];
                        if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                        if (locked[nr][nc]) continue;
                        if (tdist[nr][nc] != -1) continue;
                        tdist[nr][nc] = tdist[cr][cc] + 1;
                        q.push({nr, nc});
                    }
                }
                if (cands.empty()) continue;
                sort(cands.begin(), cands.end());
                if ((int)cands.size() > candLimit) cands.resize(candLimit);

                auto savedBoard = board;
                int savedEr = er, savedEc = ec;
                size_t savedLen = moves.size();

                int bestLen = INT_MAX, bestBr = -1, bestBc = -1;
                string bestMoves;
                vector<vector<int>> bestBoard;
                int bestEr = 0, bestEc = 0;

                for (auto &cand : cands) {
                    int br = cand.second.first, bc = cand.second.second;
                    board = savedBoard;
                    er = savedEr; ec = savedEc;
                    moves.resize(savedLen);
                    if (!moveTile(br, bc, r, c)) continue;
                    int len = (int)moves.size();
                    if (len < bestLen) {
                        bestLen = len;
                        bestBr = br; bestBc = bc;
                        bestMoves = moves;
                        bestBoard = board;
                        bestEr = er; bestEc = ec;
                    }
                }

                if (bestBr == -1) {
                    board = savedBoard;
                    er = savedEr; ec = savedEc;
                    moves.resize(savedLen);
                    continue;
                }
                moves = bestMoves;
                board = bestBoard;
                er = bestEr; ec = bestEc;
                locked[r][c] = true;
            }
        }
        moves += 'S';
        cout << moves << endl;
    }
    return 0;
}
