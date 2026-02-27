#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void selection_sort(vector<int> &v) {
    int n = v.size() - 1;
    for (int i = n; i >= 0; i--) {
        int max_v = 0; 
        for (int j = 0; j <= i; j++) {
            if (v[max_v] < v[j]) {
                max_v = j;
            }
        }
        swap(v[i], v[max_v]);
    }
}

int main() {
    vector<int> v = {1, 4, 2, 4, 9, 7, 3};
    selection_sort(v);

    for (int &x : v) cout << x << " ";
}