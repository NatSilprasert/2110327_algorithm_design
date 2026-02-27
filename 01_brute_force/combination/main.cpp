#include <iostream>

using namespace std;

void combi(vector<int> &v, int size, int i) {
    if (i == size) {
        for (int &x : v) cout << x;
        cout << endl;
        return;
    };

    for (int j = 0; j <= 1; j++) {
        v[i] = j;
        combi(v, size, i + 1);
    }
}

int main() {
    vector<int> v(3);
    combi(v, 3, 0);
    
    return 0;
}