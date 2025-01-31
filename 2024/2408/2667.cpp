#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    vector<vector<bool>> visit(n, vector<bool>(n));
    int mx[] = {-1, 0, 0, 1};
    int my[] = {0, 1, -1, 0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%1d", &v[i][j]);
        }
    }
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visit[i][j] == true || v[i][j] == 0)
                continue;
            queue<pair<int, int>> q;
            int cnt = 1;
            q.push({i, j});
            visit[i][j] = true;
            while (!q.empty())
            {
                for (int k = 0; k < 4; k++)
                {
                    int nx = q.front().first + mx[k];
                    int ny = q.front().second + my[k];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= n || v[nx][ny] == 0 || visit[nx][ny] == true)
                        continue;
                    visit[nx][ny] = true;
                    q.push({nx, ny});
                    cnt++;
                }
                q.pop();
            }
            pq.push(cnt);
        }
    }
    cout << pq.size() << '\n';
    while (!pq.empty())
    {
        cout << pq.top() << '\n';
        pq.pop();
    }
    return 0;
}