#include <iostream>
#include <vector>

using namespace std;

int ans;

void bsnr(vector<int> &v, int start, int stop, int target) {
    if (start > stop) return;
    
    int m = (start + stop) / 2;

    if (v[m] <= target) {
        ans = m;
        return bsnr(v, m + 1, stop, target);
    }
    else {
        return bsnr(v, start, m - 1, target);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    for (int i = 0; i < m; i++) {
        int target;
        cin >> target;

        ans = -1;
        bsnr(v, 0, n - 1, target);

        cout << ans << endl;
    }

    return 0;
}