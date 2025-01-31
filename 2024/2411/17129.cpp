#include <iostream>
#include <queue>

using namespace std;

int mx[] = {-1, 0, 0, 1};
int my[] = {0, 1, -1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    int mindist = 10000;
    int v[3000][3000] = {0}, visit[3000][3000] = {0};
    int stx, sty; // 시작점 좌표 저장
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (size_t j = 0; j < s.size(); j++)
        {
            v[i][j] = s[j] - '0';
            if (v[i][j] == 2)
            {
                stx = i;
                sty = j;
            }
        }
    }

    queue<pair<pair<int, int>, int>> q; // 좌표, 시작점으로부터 거리 저장
    q.push({{stx, sty}, 0});
    visit[stx][sty] = 1;
    while (!q.empty())
    {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int dist = q.front().second;
        if (v[x][y] > 2)
        {
            if (dist < mindist)
                mindist = dist;
        }
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = x + mx[i];
            int ny = y + my[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || visit[nx][ny] == 1 || v[nx][ny] == 1)
                continue;
            visit[nx][ny] = 1;
            q.push({{nx, ny}, dist + 1});
        }
    }

    if (mindist == 10000)
        cout << "NIE";
    else
        cout << "TAK\n"
             << mindist;
    return 0;
}