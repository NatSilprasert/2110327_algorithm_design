#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<int> &v) {
    int n = v.size() - 1;
    for (int i = n - 1; i >= 0; i--) {
        int tmp = v[i];
        int idx = i + 1;
        while (idx <= n && tmp > v[idx]) {
            v[idx - 1] = v[idx];
            idx++;
        }
        v[idx - 1] = tmp;
    }
}

int main()
{
    vector<int> v = {1, 4, 2, 4, 9, 7, 3};

    insertion_sort(v);

    for (int x : v) cout << x << " ";
}