#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int mx[] = {-1, 0, 0, 1};
int my[] = {0, 1, -1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int a = 0; a < t; a++)
    {
        int m, n, k;
        cin >> m >> n >> k;
        vector<vector<int>> v(m, vector<int>(n));
        vector<vector<bool>> visit(m, vector<bool>(n));
        int x, y;
        for (int b = 0; b < k; b++)
        {
            cin >> x >> y;
            v[x][y] = 1;
        }
        int cnt = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visit[i][j] == true || v[i][j] == 0)
                    continue;
                queue<pair<int, int>> q;
                visit[i][j] = true;
                cnt++;
                q.push({i, j});
                int x, y;
                while (!q.empty())
                {
                    x = q.front().first;
                    y = q.front().second;
                    for (int k = 0; k < 4; k++)
                    {
                        if (x + mx[k] < 0 || y + my[k] < 0 || x + mx[k] >= m || y + my[k] >= n || v[x + mx[k]][y + my[k]] == 0 || visit[x + mx[k]][y + my[k]] == true)
                            continue;
                        visit[x + mx[k]][y + my[k]] = true;
                        q.push({x + mx[k], y + my[k]});
                    }
                    q.pop();
                }
            }
        }
        cout << cnt << '\n';
    }
}
