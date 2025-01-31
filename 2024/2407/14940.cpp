#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int mx[] = {-1, 0, 0, 1};
int my[] = {0, -1, 1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<vector<bool>> visit(n, vector<bool>(m));
    int g1, g2; // 목표지점 좌표
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 2)
            {
                g1 = i;
                g2 = j;
            }
        }
    }
    queue<pair<pair<int, int>, int>> q;
    vector<vector<int>> map(n, vector<int>(m, 0));
    int x = g1, y = g2, weight = 0;
    q.push({{x, y}, weight});
    map[x][y] = weight;
    visit[x][y] = true;
    while (!q.empty())
    {
        x = q.front().first.first;
        y = q.front().first.second;
        weight = q.front().second;
        for (int i = 0; i < 4; i++)
        {
            if (x + mx[i] < 0 || y + my[i] < 0 || x + mx[i] >= n || y + my[i] >= m || v[x + mx[i]][y + my[i]] == 0 || visit[x + mx[i]][y + my[i]] == true)
                continue;
            visit[x + mx[i]][y + my[i]] = true;
            q.push({{x + mx[i], y + my[i]}, weight + 1});
            map[x + mx[i]][y + my[i]] = weight + 1;
        }
        q.pop();
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visit[i][j] == false && v[i][j] != 0)
                cout << -1 << ' ';
            else
                cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}