#include <iostream>
#include <vector>

using namespace std;

int n, ans = 0;
vector<int> v;
int countNum[4] = {0};

int main() {
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        countNum[v[i]]++;
    }
    
    for (int i = 0; i < countNum[1]; i++) {
        if (v[i] == 2) {
            for (int j = countNum[1]; j < n; j++) {
                if (v[j] == 1) {
                    swap(v[i], v[j]);
                    ans++;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < countNum[1]; i++) {
        if (v[i] == 3) {
            for (int j = countNum[1]; j < n; j++) {
                if (v[j] == 1) {
                    swap(v[i], v[j]);
                    ans++;
                    break;
                }
            }
        }
    }

    for (int i = countNum[1]; i < countNum[1] + countNum[2]; i++) {
        if (v[i] == 3) ans++;
    }

    cout << ans;

    return 0;
}