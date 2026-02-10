#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int n;
vector<int> v(n);
vector<int> p(n);

int max_ds(int start, int stop) {
    if (start >= stop) return v[start];

    int m = (start + stop) / 2;
    int left = max_ds(start, m);
    int right = max_ds(m + 1, stop);

    unordered_map<int, int> max_sum_left;
    unordered_map<int, int> max_sum_right;

    // left
    for (int i = start; i <= m; i++) {
        int total_sum = p[m] - p[i] + v[i];
        if (!max_sum_left.count(v[i])) {
            max_sum_left[v[i]] = total_sum;
        }
        else {
            max_sum_left[v[i]] = max(max_sum_left[v[i]], total_sum);
        }
    }

    // right
    for (int i = m + 1; i <= stop; i++) {
        int total_sum = p[i] - p[m];
        if (!max_sum_right.count(v[i])) {
            max_sum_right[v[i]] = total_sum;
        }
        else {
            max_sum_right[v[i]] = max(max_sum_right[v[i]], total_sum);
        }
    }

    // merge left and right
    int maxSum = max(left, right);
    for (auto &e : max_sum_left) {
        auto it = max_sum_right.find(e.first);
        if (it != max_sum_right.end()) {
            maxSum = max(maxSum, e.second + it->second);
        }
    }

    return maxSum;
}

int main() {
    cin >> n;
    v.resize(n);
    p.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    p[0] = v[0];
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1] + v[i];
    }

    cout << max_ds(0, n - 1);
}