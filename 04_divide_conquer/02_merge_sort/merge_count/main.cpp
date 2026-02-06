#include <iostream>
#include <vector>

using namespace std;

int n, k, c = 1;

void recur(vector<int> &v, int start, int stop) {
    if (c == k || stop - start == 1) return;
    c += 2; // number of recur calls

    int m = (stop + start) / 2;
    swap(v[m], v[m - 1]); // [1,2,3,4] -> [1,3,2,4]

    recur(v, start, m);
    recur(v, m , stop);
}

int main() {
    cin >> n >> k;

    // wrong condition
    if (k % 2 == 0 || k > 2 * n - 1) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> v(n);
    for (int i = 0; i < n; i++) 
        v[i] = i + 1;

    recur(v, 0, n);

    for (int &x : v)
        cout << x << " ";

    return 0;
}