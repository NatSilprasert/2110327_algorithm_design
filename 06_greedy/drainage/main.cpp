#include <iostream>
#include <vector>

using namespace std;

int maxV = -1.e9;
int N, L, ans = 0;
vector<int> v;
vector<int> covered;

int main() {
    cin >> N >> L; 
    v.assign(1000005, 0);
    covered.assign(1000005 + L, 0);

    for (int i = 1; i <= N; i++) {
        int x;
        cin >> x;
        v[x] = 1;
        maxV = max(maxV, x);
    }

    v.resize(maxV + 1);
    covered.resize(maxV + 1);

    for (int i = maxV; i >= 1; i--) {
        if (v[i] == 1 && !covered[i]) {
            int left = max(0, i - L + 1);
            for (int j = i; j >= left; j--) {
                covered[j] = 1;
            }
            ans++;
        } 
    }

    cout << ans;

    return 0;
}