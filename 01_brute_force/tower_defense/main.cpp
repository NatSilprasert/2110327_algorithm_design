#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n, m, k, w;
    cin >> n >> m >> k >> w;

    vector<int> p(m);
    unordered_map<int, int> h(n);
    vector<int> t(k);

    for (int i = 0; i < m; i++) {
        int monsterPos;
        cin >> monsterPos;
        p[i] = monsterPos; 
    }

    for (int i = 0; i < m; i++) {
        int monsterHp;
        cin >> monsterHp;
        h[p[i]] = monsterHp;
    }

    for (int i = 0; i < k; i++) {
        int tower;
        cin >> tower;

        int startIdx = tower - w >= 0 ? tower - w : 0;
        int endIdx = tower + w <= n ? tower + w : n;

        for (int j = startIdx; j <= endIdx; j++) {
            if (h.count(j) && h[j] > 0) {
                h[j] -= 1;
                break;
            }
        }
    }

    int sum = 0;
    for (auto x : h) {
        sum += x.second;
    }

    cout << sum;

    return 0;
}