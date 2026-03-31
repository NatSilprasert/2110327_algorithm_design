#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> go_to(n);
    vector<int> deg_in(n, 0);

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        go_to[u].push_back(v);
        deg_in[v]++;
    }

    for (int i = 0; i < 5; i++) {
        bool success = true;
        vector<int> tmp_deg_in = deg_in;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            x--;
            if (!success) continue;

            if (tmp_deg_in[x] != 0) {
                success = false;
                continue;
            }
            for (int next : go_to[x]) {
                tmp_deg_in[next]--;
            }
        }
        if (success) cout << "SUCCESS" << endl;
        else cout << "FAIL" << endl;
    }

    return 0;
}