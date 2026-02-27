#include <iostream>
#include <vector>

using namespace std;

void shell_sort(vector<int> &v) {
    int n = v.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j = i;
            while (j >= gap && v[j - gap] > temp) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = temp;
        }
    }
}

int main() {
    vector<int> v = {1, 4, 2, 4, 9, 7, 3};

    shell_sort(v);

    for (int x : v)
        cout << x << " ";
}