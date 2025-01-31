#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        vector<bool> visit(n);
        queue<int> q;
        for (int j = 0; j < n; j++)
        {
            if (v[i][j] == 1)
            {
                ans[i][j] = 1;
                visit[j] = true;
                q.push(j);
            }
        }
        while (!q.empty())
        {
            int node = q.front();
            for (int k = 0; k < n; k++)
            {
                if (visit[k] == true)
                    continue;
                if (v[node][k] == 1)
                {
                    ans[i][k] = 1;
                    visit[k] = true;
                    q.push(k);
                }
            }
            q.pop();
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
}