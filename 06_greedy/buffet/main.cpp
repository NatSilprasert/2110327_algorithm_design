#include <iostream>
#include <vector>

using namespace std;

int f, w, n;
vector<int> table;
vector<int> covered;

int main() {
    cin >> f >> w >> n;
    table.assign(n + 1, 0);
    covered.assign(n + 1, 0);
    for (int i = 1; i <= f; i++) {
        int x;
        cin >> x;
        table[x] = 1;
    }

    int count = 0;
    int L = 1 + 2 * w;
    for (int i = 1; i <= n; i++) {
        if (table[i] == 1 && !covered[i]) {
            count++;
            for (int j = i; j <= min(n, i + L - 1); j++) {
                covered[j] = 1;
            }
        }
    }

    cout << count;

    return 0;
}