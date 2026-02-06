#include <iostream>
#include <vector>

using namespace std;

int c = 0;

void merge(vector<int> &v, int start, int m, int stop, vector<int> &tmp) {
    int bi = start; // index b
    int ci = m + 1; // index c
    for (int i = start; i <= stop; i++) {
        if (bi > m)     {tmp[i] = v[ci++]; continue;}
        if (ci > stop)  {tmp[i] = v[bi++]; continue;}
        
        if (v[bi] > v[ci]) {
            tmp[i] = v[ci++];
            c += (m - bi + 1); // e.g. v[ci] = 2 so (2, 3), (2, 4), ...
        }
        else {
            tmp[i] = v[bi++];
        }
    }
    for (int i = start; i <= stop; i++) v[i] = tmp[i];
}

void merge_sort(vector<int> &v , int start, int stop, vector<int> &tmp) {
    if (start < stop) {
        int m = (start + stop) / 2;
        merge_sort(v, start, m, tmp);
        merge_sort(v, m + 1, stop, tmp);
        merge(v, start, m, stop, tmp);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> tmp(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    merge_sort(v, 0, n - 1, tmp);

    cout << c;

    return 0;
}