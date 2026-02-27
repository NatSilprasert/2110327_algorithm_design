#include <iostream>

using namespace std;

void permu(vector<int> &v, vector<int> &used, int size, int i) {
   if (i == size) {
        for (int &x : v)
            cout << x;
        cout << endl;
        return;
    };

    for (int j = 1; j <= size; j++) {
        if (used[j] == 0) {
            v[i] = j;
            used[j] = 1;
            permu(v, used, size, i + 1);
            used[j] = 0;
        }
    }
}

int main() {
    vector<int> v(3);
    vector<int> used(4, 0);
    permu(v, used, 3, 0);

    return 0;
}