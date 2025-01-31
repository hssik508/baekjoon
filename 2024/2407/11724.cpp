#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(n));
    vector<bool> visit(n);
    int n1, n2;
    for (int i = 0; i < m; i++)
    {
        cin >> n1 >> n2;
        v[n1 - 1][n2 - 1] = 1;
        v[n2 - 1][n1 - 1] = 1;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (visit[i - 1] == true)
            continue;
        queue<int> q;
        q.push(i);
        visit[i - 1] = true;
        int node;
        while (!q.empty())
        {
            node = q.front();
            for (int j = 0; j < n; j++)
            {
                if (visit[j] == true)
                    continue;
                if (v[node - 1][j] == 1)
                {
                    q.push(j + 1);
                    visit[j] = true;
                }
            }
            q.pop();
        }
        cnt++;
    }
    cout << cnt;
    return 0;
}