#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int virus(vector<int> &v, int start, int stop) {
    if (start < stop) {
        int m = (stop + start) / 2;

        int left = virus(v, start, m);
        int right = virus(v, m + 1, stop);

        if (abs(left - right) > 1) {
            return 9999999; // for always "no"
        }
        else {
            return left + right;
        }
    }
    return v[start];
}

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int size = pow(2, k);
        vector<int> v(size);

        for (int j = 0; j < size; j++) {
            cin >> v[j];
        }

        if (virus(v, 0, size - 1) <= 999999) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }

    return 0;
}