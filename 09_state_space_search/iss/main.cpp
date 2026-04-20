#include <iostream>

using namespace std;

int n, result = 0;

void iss(int sum, int idx) {
    if (sum >= n || idx + sum > n) {
        if (sum == n) result++;
        return;
    }
    iss(sum + idx, idx); // use current
    iss(sum, idx + 1); // skip current
}

int main() {
    cin >> n;
    iss(0, 1);
    cout << result;
    return 0;
}