#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

int mss(vector<int> &v, int start, int stop) {
    if (stop - start < 0) return INT_MIN;
    if (start == stop) return v[start];

    int currentSum = v[start];
    int maxSum = v[start];
    for (int i = start + 1; i <= stop; i++) {
        currentSum = max(currentSum + v[i], v[i]);
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int currSum = v[0];
    int maxSum = v[0];
    int maxStart = 0;
    int tempStart = 0;
    int maxStop = 0;

    for (int i = 1; i < n; i++) {
        if (currSum + v[i] > v[i]) {
            currSum += v[i];
        }
        else {
            currSum = v[i];
            tempStart = i;
        }

        if (currSum >= maxSum) {
            maxSum = currSum;
            maxStop = i;
            maxStart = tempStart;
        }        
    }

    int maxSumLeft = mss(v, 0, maxStart - 1);
    int maxSumRight = mss(v, maxStop + 1, n - 1);
    int secondMaxSum(max(maxSumLeft, maxSumRight));

    // cout << maxStart << " " << maxStop << endl;
    // cout << "maxSum: " << maxSum << endl;
    // cout << "maxSumLeft: " << maxSumLeft << endl;
    // cout << "maxSumRight: " << maxSumRight << endl;
    cout << max(maxSum, maxSum + secondMaxSum);

    return 0;
}