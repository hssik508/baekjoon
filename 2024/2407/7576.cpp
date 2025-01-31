#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int mx[] = {-1, 0, 0, 1};
int my[] = {0, 1, -1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int m, n;
    cin >> m >> n;
    vector<vector<int>> v(n, vector<int>(m));
    vector<vector<bool>> visit(n, vector<bool>(m));
    queue<pair<pair<int, int>, int>> q;
    int zero = 0, weight = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 0)
                zero = 1;
            if (v[i][j] == 1)
            {
                q.push({{i, j}, weight});
                visit[i][j] = true;
            }
        }
    }
    if (zero == 0)
    {
        cout << 0;
        return 0;
    }
    int x, y, maxWeight = 0;
    while (!q.empty())
    {
        x = q.front().first.first;
        y = q.front().first.second;
        weight = q.front().second;
        if (weight > maxWeight)
            maxWeight = weight;
        for (int k = 0; k < 4; k++)
        {
            int nx = x + mx[k];
            int ny = y + my[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || visit[nx][ny] == true || v[nx][ny] == -1)
                continue;
            visit[nx][ny] = true;
            q.push({{nx, ny}, weight + 1});
        }
        q.pop();
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i][j] == 0 && visit[i][j] == false)
            {
                cout << -1;
                return 0;
            }
        }
    }
    cout << maxWeight;
    return 0;
}
