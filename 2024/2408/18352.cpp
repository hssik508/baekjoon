#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<vector<int>> v(n + 1);
    vector<bool> visit(n + 1);
    vector<int> city(n + 1);
    int n1, n2;
    for (int i = 0; i < m; i++)
    {
        cin >> n1 >> n2;
        v[n1].push_back(n2);
    }
    queue<pair<int, int>> q;
    visit[x] = true;
    int node, dist = 1, sameK = 0;
    for (size_t i = 0; i < v[x].size(); i++)
    {
        q.push({v[x][i], dist});
        visit[v[x][i]] = true;
        if (k == dist)
        {
            city[v[x][i]] = 1;
            q.pop();
            sameK = 1;
        }
    }
    while (!q.empty())
    {
        node = q.front().first;
        dist = q.front().second;
        if (dist == k)
            sameK = 1;
        for (size_t i = 0; i < v[node].size(); i++)
        {
            if (visit[v[node][i]] == false)
            {
                q.push({v[node][i], dist + 1});
                visit[v[node][i]] = true;
                if (dist + 1 == k)
                    city[v[node][i]] = 1;
            }
        }
        q.pop();
    }
    if (sameK == 0)
    {
        cout << -1;
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        if (city[i] == 1)
            cout << i << '\n';
    }
    return 0;
}