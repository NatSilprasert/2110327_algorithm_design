#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a = 0;
    int b = 1;

    for (int i = 2; i <= n; i++) {
        int tmp = b;
        b += a;
        a = tmp;
    }
    cout << b;

    return 0;
}