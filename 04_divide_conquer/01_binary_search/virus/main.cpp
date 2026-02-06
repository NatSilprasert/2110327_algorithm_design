#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool isDivoc(vector<int> v, int k) {
    if (k == 1) {
        return (v.size() == 2 && v[0] == 0 && v[1] == 1);
    }

    int m = v.size() / 2;

    vector<int> left(v.begin(), v.begin() + m);
    vector<int> right(v.begin() + m, v.end());

    if (!isDivoc(right, k - 1)) {
        return false;
    }

    bool leftNormal = isDivoc(left, k - 1);

    reverse(left.begin(), left.end());
    bool leftReversed = isDivoc(left, k - 1);

    return leftNormal || leftReversed;
}

int main() {
    int n, m;
    cin >> n >> m;
    int size = pow(2, m);

    for (int i = 0; i < n; i++) {
        vector<int> v(size);
        for (int j = 0; j < size; j++) {
            cin >> v[j];
        }

        if (isDivoc(v, m)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
    return 0;
}