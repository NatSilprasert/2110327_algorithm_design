#include <iostream>
#include <vector> 

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    int totalSum = v[0];
    int currSum = v[0];
    int maxSum = v[0];
    int currMin = v[0];
    int maxMin = v[0];

    for (int i = 1; i < n; i++) {
        totalSum += v[i];
        currSum = max(currSum + v[i], v[i]);
        maxSum  = max(currSum, maxSum);

        currMin = min(currMin + v[i], v[i]);
        maxMin = min(currMin, maxMin);
    }

    if (maxSum < 0) {
        cout << maxSum;
    }
    else cout << max(maxSum, totalSum - maxMin);

    return 0;
}