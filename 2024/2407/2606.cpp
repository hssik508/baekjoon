#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(n));
    vector<bool> visit(n);
    int x, y;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        v[x - 1][y - 1] = 1;
        v[y - 1][x - 1] = 1;
    }
    queue<int> q;
    q.push(1);
    visit[0] = true;
    int cnt = 0;
    while (!q.empty())
    {
        int node = q.front();
        for (int i = 0; i < n; i++)
        {
            if (visit[i] == true)
                continue;
            if (v[node - 1][i] == 1)
            {
                q.push(i + 1);
                cnt++;
                visit[i] = true;
            }
        }
        q.pop();
    }
    cout << cnt;
    return 0;
}