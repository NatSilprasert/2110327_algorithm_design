#include <iostream>
using namespace std;

long long mod_expo(long long a, long long n, long long k) {
    if (n == 0) return 1 % k;
    if (n == 1) return a % k;

    long long tmp = mod_expo(a, n/2, k);
    tmp = (tmp * tmp) % k;

    if (n % 2 == 1) {
        tmp = (tmp * a) % k;
    }

    return tmp;
}

int main() {
    long long a = 3, n = 13, k = 7;
    cout << mod_expo(a, n, k); // output: 3^13 % 7
}

