#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> v;
vector<int> w;
int dp[505][505];

int main()
{
    cin >> n >> m;

    v.resize(n + 1);
    w.resize(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> v[i];
    for (int i = 1; i <= n; i++)
        cin >> w[i];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            cin >> dp[i][j];
        }
    }

    int currW = m;
    vector<int> ans;

    for (int i = n; i >= 1; i--)
    {
        if (dp[i][currW] != dp[i - 1][currW])
        {
            ans.push_back(i);
            currW -= w[i];
        }
    }

    cout << ans.size() << endl;
    for (int x : ans)
        cout << x << " ";

    return 0;
}