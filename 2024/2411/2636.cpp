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
    int cheezeCnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
            if (v[i][j] == 1)
                cheezeCnt++;
        }
    }
    int cnt = 0;
    vector<int> lastcheezeCnt;
    lastcheezeCnt.push_back(cheezeCnt); // 매 사이클마다 치즈 개수 저장
    while (1)
    {
        if (cheezeCnt == 0)
            break;
        vector<pair<int, int>> melt; // 매 사이클마다 녹을 예정인 치즈 좌표 저장
        vector<vector<bool>> visit(n, vector<bool>(m));
        queue<pair<int, int>> q;
        q.push({0, 0}); // 왼쪽 맨 위 X자 표시에서 탐색 시작
        visit[0][0] = true;
        while (!q.empty())
        {
            int x = q.front().first;
            int y = q.front().second;
            for (int k = 0; k < 4; k++)
            {
                int nx = x + mx[k];
                int ny = y + my[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || visit[nx][ny] == true)
                    continue;
                visit[nx][ny] = true;
                if (v[nx][ny] == 1) // 녹을 예정인 치즈 좌표 저장
                    melt.push_back({nx, ny});
                else
                    q.push({nx, ny});
            }
            q.pop();
        }
        cnt++;
        cheezeCnt -= (size_t)melt.size();
        lastcheezeCnt.push_back(cheezeCnt);
        for (size_t i = 0; i < melt.size(); i++) // 녹게 된 치즈 위치 값 0으로 재설정
        {
            v[melt[i].first][melt[i].second] = 0;
        }
    }
    cout << cnt << '\n'
         << lastcheezeCnt[lastcheezeCnt.size() - 2]; // 배열 맨 마지막 값은 0 이므로 맨 끝에서 2번째 값 가져와야 함
    return 0;
}