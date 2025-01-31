#include <iostream>
#include <queue>

using namespace std;

int mx[]={-1,0,0,1};
int my[]={0,-1,1,0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin>>v[i][j];
        }
    }
    int time=0; // 치즈가 모두 녹아서 없어질 때까지 시간
    while (1) // 치즈가 모두 사라질때까지 반복
    {
        queue<pair<int,int>> q;
        vector<vector<bool>> visit(n, vector<bool>(m));
        vector<pair<int,int>> cheeze_with_air; // 외부 공기와 접촉한 치즈
        q.push({0,0});
        visit[0][0]=true;
        while (!q.empty())
        {
            int x=q.front().first;
            int y=q.front().second;
            q.pop();
            for (int i=0; i<4; i++)
            {
                int nx=x+mx[i];
                int ny=y+my[i];
                if (nx<0 || ny<0 || nx>=n || ny>=m || visit[nx][ny]==true)
                    continue;
                if (v[nx][ny]==1)
                    cheeze_with_air.push_back({nx, ny});
                else // 외부 공기 좌표만 방문처리 & 큐에 삽입
                {
                    visit[nx][ny]=true;
                    q.push({nx, ny});
                }
            }
        }
        if (cheeze_with_air.size()==0)
            break;
        else
            time++;
        for (size_t i=0; i<cheeze_with_air.size(); i++)
        {
            int x=cheeze_with_air[i].first;
            int y=cheeze_with_air[i].second;
            int airCnt=0;
            for (int k=0; k<4; k++)
            {
                int nx=x+mx[k];
                int ny=y+my[k];
                if (nx<0 || ny<0 || nx>=n || ny>=m || visit[nx][ny]==false)
                    continue;
                airCnt++;
            }
            if (airCnt>=2)
                v[x][y]=0;
        }
    }
    cout<<time;
    return 0;
}