#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    int x, y;
    int mx[] = {-1, 0, 0, 1};
    int my[] = {0, -1, 1, 0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 9)
            {
                x = i;
                y = j;
            }
        }
    }

    int sharksize = 2, dist, cnt = 0;   // 현재 아기 상어 크기, 누적 거리, cnt가 size와 동일해져야 아기상어 크기 성장
    int sec = 0;                    // 마지막으로 물고기 먹었을 때의 시간 저장(더이상 물고기 먹을게 없으면 tempsec에 저장한 시간 출력)
    queue<pair<pair<int, int>, int>> q; // 좌표와 거리 저장
    q.push({{x, y}, 0});                // 아기 상어 최초 위치 저장
    while (1)
    {
        vector<pair<int, pair<int, int>>> arr;
        vector<vector<bool>> visit(n, vector<bool>(n));
        v[q.front().first.first][q.front().first.second] = 0;
        visit[q.front().first.first][q.front().first.second] = true;
        while (!q.empty())
        {
            x = q.front().first.first;
            y = q.front().first.second;
            dist = q.front().second;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + mx[i];
                int ny = y + my[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= n || v[nx][ny] > sharksize || visit[nx][ny] == true)
                    continue;
                visit[nx][ny] = true;
                q.push({{nx, ny}, dist + 1});
                if (v[nx][ny] != 0 && v[nx][ny] != sharksize)
                    arr.push_back({dist + 1, {nx, ny}});
            }
            q.pop();
        }
        if (arr.size() == 0)
            break;
        sort(arr.begin(), arr.end());
        cnt++;
        if (cnt == sharksize)
        {
            sharksize++;
            cnt = 0;
        }
        sec += arr[0].first;
        q.push({{arr[0].second.first, arr[0].second.second}, 0});
    }
    cout << sec;
    return 0;
}