#include <iostream>
#include <vector>

using namespace std;

void recursive(string num, int n, int k, int one, bool check)
{
    if (one == k) check = true;
    
    if (n == 0) 
    {
        if (check) cout << num << endl;
        return;
    }

    recursive("0" + num, n - 1, k, one, check);
    if (!check) recursive("1" + num, n - 1, k, one + 1, check);
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> k >> n;
    recursive("", n, k, 0, false);
    
    return 0;
}