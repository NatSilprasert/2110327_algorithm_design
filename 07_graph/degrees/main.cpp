#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    
    int n;
    cin >> n;
    vector<int> result(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) result[i] += 1;
        }
    }

    sort(result.begin(), result.end());

    vector<int> ans(result[n - 1] + 1, 0);
    for (int x : result) ans[x] += 1;

    for (int x : ans) cout << x << " ";

    return 0;
}