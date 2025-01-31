#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    vector<vector<bool>> visit(n, vector<bool>(m));
    int mx[] = {-1, 0, 0, 1};
    int my[] = {0, -1, 1, 0};
    int x, y, cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 'I')
            {
                x = i;
                y = j;
            }
        }
    }
    queue<pair<int, int>> q;
    q.push({x, y});
    visit[x][y] = true;
    while (!q.empty())
    {
        x = q.front().first;
        y = q.front().second;
        for (int k = 0; k < 4; k++)
        {
            int X = x + mx[k];
            int Y = y + my[k];
            if (X < 0 || Y < 0 || X >= n || Y >= m || v[X][Y] == 'X' || visit[X][Y] == true)
                continue;
            visit[X][Y] = true;
            if (v[X][Y] == 'P')
                cnt++;
            q.push({X, Y});
        }
        q.pop();
    }
    if (cnt == 0)
        cout << "TT";
    else
        cout << cnt;
    return 0;
}