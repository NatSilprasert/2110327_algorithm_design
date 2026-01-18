#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

int main()
{
    int n;
    cin >> n;

    const int MOD = 16777216;
    queue<pair<int, int>> q; // {value, steps}
    unordered_set<int> visited;

    q.push({n, 0});
    visited.insert(n);

    while (!q.empty())
    {
        int cur = q.front().first;
        int step = q.front().second;
        q.pop();

        if (cur % MOD == 0)
        {
            cout << step;
            return 0;
        }

        // operation +1
        if (!visited.count(cur + 1))
        {
            visited.insert(cur + 1);
            q.push({cur + 1, step + 1});
        }

        // operation *2
        if (!visited.count(cur * 2))
        {
            visited.insert(cur * 2);
            q.push({cur * 2, step + 1});
        }
    }
}