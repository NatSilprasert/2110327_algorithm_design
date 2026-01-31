#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, a, sum = 0, sumQ = 0;
    cin >> n >> a;
    vector<int> chef(n);

    for (int i = 0; i < n; i++) {
        cin >> chef[i];
    }

    for (int i = 0; i < a; i++) {
        long long c;
        cin >> c;
     
        long long low = 0, high = 2e14;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            long long total_seated = 0;
            for (int i = 0; i < n; i++) {
                total_seated += (mid / chef[i]) + 1;
            }

            if (total_seated >= c) {
                ans = mid;
                high = mid - 1;
            } 
            else {
                low = mid + 1;
            }
        }

        cout << ans << endl;
    }

    return 0;
}