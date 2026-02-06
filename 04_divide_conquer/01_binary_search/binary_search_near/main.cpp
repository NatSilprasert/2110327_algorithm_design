#include <iostream>
#include <vector>

using namespace std;

int ans = -1;

void bs(vector<int> &v, int start, int stop, int target) {
    if (start > stop) return;

    int m = (start + stop) / 2;

    if (v[m] <= target) {
        ans = v[m];
        return bs(v, m + 1, stop, target); 
    }
    else {
        return bs(v, start, m - 1, target);
    }
}

int main() {
    int n, m; 
    cin >> n >> m;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i]; 

    for (int i = 0; i < m; i++) {
        ans = -1;
        int input;
        cin >> input;
        bs(v, 0, n - 1, input);
        cout << ans << endl;
    }

    return 0;
}