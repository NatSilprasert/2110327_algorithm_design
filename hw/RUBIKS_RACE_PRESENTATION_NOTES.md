# Rubik's Race - เอกสารประกอบการอธิบาย

## 1) Problem Setup
- Input: กระดาน `N x N` มีช่องว่าง `-1` หนึ่งช่อง
- Goal: ทำให้พื้นที่กลาง `(N-2) x (N-2)` ตรงกับ target
- Output: สตริงคำสั่ง `U/D/L/R` และลงท้ายด้วย `S`
- Scoring: ใช้ move น้อยกว่า = คะแนนดีกว่า

### โค้ดประกอบ (อ่าน input + target)
```cpp
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
```

---

## 2) Key Idea: Hybrid Strategy
- ถ้า `N == 5` ใช้ **IDA\*** (เน้นคุณภาพคำตอบ)
- ถ้า `N > 5` ใช้ **Greedy + BFS** (เน้นความเร็วและ scale)

เหตุผล:
- IDA\* ดีมากสำหรับบอร์ดเล็ก แต่แพงมากเมื่อ N ใหญ่
- Greedy+BFS ไม่ optimal แต่เร็วพอสำหรับ test ขนาด 33, 51, 67

### โค้ดประกอบ (เลือกวิธีตามขนาดบอร์ด)
```cpp
if (N == 5) {
    // IDA* with min-cost matching heuristic
    ...
    cout << path << "S" << endl;
} else {
    // Greedy with best-candidate selection for larger N
    ...
    moves += 'S';
    cout << moves << endl;
}
```

---

## 3) N == 5: IDA* + Matching Heuristic

### 3.1 State & Transition
- state = board + position ของช่องว่าง
- move ได้ 4 ทิศ
- prune: ห้าม reverse ทันที (`k == (prevDir ^ 1)`)

### โค้ดประกอบ (ทิศทางและคำสั่ง)
```cpp
int drs[] = {-1, 1, 0, 0};
int dcs[] = {0, 0, -1, 1};
char cmdChar[] = {'D', 'U', 'R', 'L'};
```

### 3.2 Heuristic Design (รองรับสีซ้ำ)
- แยกตำแหน่งเป้าหมายตามสี: `tgtByColor[color]`
- แยกตำแหน่งปัจจุบันตามสี
- หา minimum assignment cost ต่อสี (Manhattan)
- รวมทุกสีเป็น `h(state)`

### โค้ดประกอบ (assignment DP + heuristic)
```cpp
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
            int d = abs(tgt[ti].first - src[si].first)
                  + abs(tgt[ti].second - src[si].second);
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
```

### 3.3 IDA* Control Loop
- เริ่ม `limit = h(initial)`
- DFS เงื่อนไข `g + h <= limit`
- ถ้าเกิน limit บันทึก `nextLimit` ต่ำสุด
- อัปเดต limit และวนจน `h == 0`

### โค้ดประกอบ (IDA* loop + prune reverse move)
```cpp
void idaDFS(vector<vector<int>>& b, int r, int c, int prevDir, int g, string& path) {
    int h = heuristic(b);
    int f = g + h;
    if (f > idaLimit) { idaNextLimit = min(idaNextLimit, f); return; }
    if (h == 0) { idaSolved = true; return; }
    for (int k = 0; k < 4; k++) {
        if (prevDir != -1 && k == (prevDir ^ 1)) continue;
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

idaLimit = heuristic(board);
string path;
while (!idaSolved) {
    idaNextLimit = INT_MAX;
    idaDFS(board, er, ec, -1, 0, path);
    if (idaSolved) break;
    if (idaNextLimit == INT_MAX) break;
    idaLimit = idaNextLimit;
}
```

---

## 4) N > 5: Greedy + BFS Routing

### 4.1 Fill Center Incrementally
- ไล่ช่องเป้าหมายกลางกระดานทีละช่อง
- ถ้าช่องถูกต้องแล้ว -> lock
- หา candidate tile สีที่ต้องการด้วย BFS
- ทดลองหลาย candidate ใกล้สุด แล้วเลือก move เพิ่มน้อยสุด

### โค้ดประกอบ (ล็อกช่อง + ลองหลาย candidate)
```cpp
if (board[r][c] == want) {
    locked[r][c] = true;
    continue;
}
...
sort(cands.begin(), cands.end());
if ((int)cands.size() > candLimit) cands.resize(candLimit);
...
if (!moveTile(br, bc, r, c)) continue;
int len = (int)moves.size();
if (len < bestLen) {
    bestLen = len;
    bestMoves = moves;
    bestBoard = board;
    bestEr = er; bestEc = ec;
}
...
moves = bestMoves;
board = bestBoard;
er = bestEr; ec = bestEc;
locked[r][c] = true;
```

### 4.2 Core Functions
- `moveEmptyTo(tr, tc, forbidR, forbidC)`  
  ย้ายช่องว่างด้วย BFS โดยหลบ lock และ tile ที่กำลังดัน

- `moveTile(sr, sc, tr, tc)`  
  วางเส้นทาง tile ด้วย BFS และดันทีละก้าวผ่าน `moveEmptyTo`

### โค้ดประกอบ (`moveEmptyTo`)
```cpp
bool moveEmptyTo(int tr, int tc, int forbidR, int forbidC) {
    if (er == tr && ec == tc) return true;
    vector<vector<int>> dist(N, vector<int>(N, -1));
    vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    q.push({er, ec});
    dist[er][ec] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
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
    ...
}
```

### โค้ดประกอบ (`moveTile`)
```cpp
bool moveTile(int sr, int sc, int tr, int tc) {
    ...
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
    ...
    if (!moveEmptyTo(nr, nc, cur_tr, cur_tc)) return false;
    ...
}
```

---

## 5) Command Mapping (สำคัญมาก)
- `U`: tile ใต้ขึ้น (empty ลง)
- `D`: tile บนลง (empty ขึ้น)
- `L`: tile ขวาซ้าย (empty ขวา)
- `R`: tile ซ้ายขวา (empty ซ้าย)
- ปิดท้ายด้วย `S`

สอดคล้องกับไฟล์ตรวจ `algo-hw-25/board.cpp`

### โค้ดประกอบ (mapping จริงในโปรแกรม)
```cpp
// k=0: empty up   -> cmd='D'
// k=1: empty down -> cmd='U'
// k=2: empty left -> cmd='R'
// k=3: empty right-> cmd='L'
int drs[] = {-1, 1, 0, 0};
int dcs[] = {0, 0, -1, 1};
char cmdChar[] = {'D', 'U', 'R', 'L'};
```

---

## 6) Complexity (ภาพรวม)
- IDA\*: exponential ตามความลึกคำตอบ (แต่ใช้เฉพาะ N=5)
- Greedy+BFS: polynomial และรันทันในเคสใหญ่

---

## 7) Experiment Results
- `1.in` = 28
- `2.in` = 3698
- `3.in` = 22293
- `4.in` = 71612
- `5.in` = 202458
- `6.in` = 506865

ทุกเคสต่ำกว่า baseline

---

## 8) Talking Points (สรุปตอนจบ)
- จุดเด่นคือ adaptive strategy ตามขนาดปัญหา
- ได้ทั้งคุณภาพคำตอบ (เคสเล็ก) และความเร็ว (เคสใหญ่)
- เหมาะกับโจทย์ Output Only ที่วัดผลด้วยจำนวน moves
