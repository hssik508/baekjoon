#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct xyz
{
    int h;
    int x;
    int y;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int m, n, h;
    cin >> m >> n >> h;
    vector<vector<vector<int>>> v(h, vector<vector<int>>(n, vector<int>(m)));
    vector<vector<vector<bool>>> visit(h, vector<vector<bool>>(n, vector<bool>(m)));
    int mh[] = {1, -1, 0, 0, 0, 0};
    int mx[] = {0, 0, 1, 0, 0, -1};
    int my[] = {0, 0, 0, -1, 1, 0};
    queue<pair<xyz, int>> q;
    int day = 0, maxday = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                cin >> v[i][j][k];
                if (v[i][j][k] == 1)
                {
                    q.push({{i, j, k}, day});
                    visit[i][j][k] = true;
                }
            }
        }
    }
    while (!q.empty())
    {
        int dayNum = q.front().second;
        if (dayNum > maxday)
            maxday = dayNum;
        for (int i = 0; i < 6; i++)
        {
            int nh = q.front().first.h + mh[i];
            int nx = q.front().first.x + mx[i];
            int ny = q.front().first.y + my[i];
            if (nh < 0 || nx < 0 || ny < 0 || nh >= h || nx >= n || ny >= m || v[nh][nx][ny] == -1 || visit[nh][nx][ny] == true)
                continue;
            visit[nh][nx][ny] = true;
            q.push({{nh, nx, ny}, dayNum + 1});
        }
        q.pop();
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                if (v[i][j][k] == 0 && visit[i][j][k] == false)
                    maxday = -1;
            }
        }
    }
    cout << maxday;
    return 0;
}