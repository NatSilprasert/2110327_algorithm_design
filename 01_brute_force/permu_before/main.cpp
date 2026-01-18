#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int n, m;
unordered_map<int, int> before;

void recur(vector<int> &result, int step, vector<bool> &used)
{
    if (step == n)
    {
        for (auto x : result)
        {
            cout << x << " ";
        }
        cout << endl;
    }

    else
    {
        for (int i = 0; i < n; i++)
        {
            if (used[i] == false && (!before.count(i) || used[before[i]]))
            {
                used[i] = true;
                result[step] = i;
                recur(result, step + 1, used);
                used[i] = false;
            }
            else
            {
                continue;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    
    vector<bool> used(n);
    vector<int> result(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        before[b] = a;
    }

    recur(result, 0, used);
}