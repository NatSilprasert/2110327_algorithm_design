#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (int i = 0; i < m; i++) {
        long long target;
        cin >> target;
        bool found = false;

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;
            
            long long sum = v[i] + v[left] + v[right];
            while (left < right && sum != target) {
                if (sum > target) right--;
                else if (sum < target) left++;
                sum = v[i] + v[left] + v[right];
            }

            if (sum == target) {
                found = true;
                break;
            }
        }
        
        if (found) cout << "YES" << endl;
        else cout << "NO" << endl;
    }


    return 0;
}