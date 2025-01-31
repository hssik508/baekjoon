#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

int mx[] = {1, 0, 0, -1};
int my[] = {0, -1, 1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, l, r;
    cin >> n >> l >> r;
    vector<vector<int>> v(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> v[i][j];
        }
    }

    int day_cnt = 0;
    while (1)
    {
        int human_move = 0; // 인구이동 있는지 여부 기록용
        vector<vector<bool>> visit(n + 1, vector<bool>(n + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (visit[i][j] == true)
                    continue;

                int movement = 0; // (i,j) 나라의 인구이동 여부 기록용
                int x = i, y = j;
                for (int k = 0; k < 4; k++)
                {
                    int nx = x + mx[k];
                    int ny = y + my[k];
                    if (nx == 0 || ny == 0 || nx > n || ny > n || abs(v[nx][ny] - v[x][y]) < l || abs(v[nx][ny] - v[x][y]) > r)
                        continue;
                    movement++;
                }

                if (movement == 0) // (i,j) 나라가 인구이동 없는 경우 다음 나라로 탐색 위치 이동
                    continue;

                human_move++;
                int sum = 0, cnt = 0;       // 연합한 국가 개수와 인구 합 구하기 위함
                queue<pair<int, int>> q;    // 연합국 탐색용 큐
                vector<pair<int, int>> arr; // 연합국 좌표 저장용
                q.push({i, j});
                visit[i][j] = true;
                while (!q.empty())
                {
                    int x = q.front().first;
                    int y = q.front().second;
                    sum += v[x][y];
                    cnt++;
                    for (int k = 0; k < 4; k++)
                    {
                        int nx = x + mx[k];
                        int ny = y + my[k];
                        if (nx == 0 || ny == 0 || nx > n || ny > n || abs(v[nx][ny] - v[x][y]) < l || abs(v[nx][ny] - v[x][y]) > r || visit[nx][ny] == true)
                            continue;
                        q.push({nx, ny});
                        visit[nx][ny] = true;
                    }
                    arr.push_back({x, y});
                    q.pop();
                }
                int new_population = sum / cnt;
                for (size_t i = 0; i < arr.size(); i++)
                {
                    v[arr[i].first][arr[i].second] = new_population;
                }
            }
        }

        if (human_move == 0)
            break;
        day_cnt++;
    }
    cout << day_cnt;
    return 0;
}