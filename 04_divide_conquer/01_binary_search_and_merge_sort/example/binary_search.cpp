#include <iostream>
#include <vector>

using namespace std;

bool binary_search(vector<int> &v, int start, int stop, int target) {
    if (start == stop) return v[start] == target ? true : false;
    int m = (start + stop) / 2;
    if (v[m] >= target) {
        return binary_search(v, start, m, target);
    }
    else {
        return binary_search(v, m + 1, stop, target);
    }
}

int main() {
    int n, target;
    cin >> n >> target;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i + 1;

    cout << binary_search(v, 0, n - 1, target) << endl;

    return 0;
}