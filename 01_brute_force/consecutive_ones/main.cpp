#include <iostream>
#include <vector>

using namespace std;

vector<string> all_nums;

void recursive(string num, int n, int k, int one, bool check)
{
    if (one >= k)
    {
        check = true;
    }

    if (n == 0)
    {
        if (check) cout << num << endl;
        return;
    }

    recursive(num + "0", n - 1, k, 0, check);
    recursive(num + "1", n - 1, k, one + 1, check);
}

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    recursive("", n, k, 0, false);
    
    return 0;
}