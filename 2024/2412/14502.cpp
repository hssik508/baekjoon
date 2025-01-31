#include <iostream>
#include <queue>

using namespace std;

int mx[]={-1,0,0,1};
int my[]={0,1,-1,0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<pair<int,int>> zero;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) 
        {
            cin>>v[i][j];
            if (v[i][j]==0)
                zero.push_back({i,j});
        }
    }
    // 벽 3개 만들 수 있는 모든 경우 고려 
    int maxCnt=0;
    for (size_t i=0; i<zero.size()-2; i++) {
        for (size_t j=i+1; j<zero.size()-1; j++) {
            for (size_t k=j+1; k<zero.size(); k++) // *** 삼중 반복문 범위설정 주의 *** 
            {
                vector<vector<int>> tmp=v; // 빈 공간에 벽을 3개 세운 상황을 저장한 임시벡터 
                vector<vector<bool>> visit(n, vector<bool>(m));
                tmp[zero[i].first][zero[i].second]=1;
                tmp[zero[j].first][zero[j].second]=1;
                tmp[zero[k].first][zero[k].second]=1;
                queue<pair<int,int>> q;
                for (int a=0; a<n; a++) {
                    for (int b=0; b<m; b++) 
                    {
                        if (tmp[a][b]==2)
                        {
                            q.push({a,b});
                            while (!q.empty()) 
                            {
                                int x=q.front().first;
                                int y=q.front().second;
                                tmp[x][y]=2; // 바이러스 감염
                                q.pop();
                                for (int c=0; c<4; c++)
                                {
                                    int nx=x+mx[c];
                                    int ny=y+my[c];
                                    if (nx<0 || ny<0 || nx>=n || ny>=m || visit[nx][ny]==true || tmp[nx][ny]!=0)
                                        continue;
                                    q.push({nx,ny});
                                    visit[nx][ny]=true;
                                }
                            }
                        }
                    }
                }
                int safeCnt=0;
                for (int a=0; a<n; a++) {
                    for (int b=0; b<m; b++) {
                        if (tmp[a][b]==0)
                            safeCnt++;
                    }
                }
                if (safeCnt>maxCnt)
                    maxCnt=safeCnt;
            }
        }
    }
    cout<<maxCnt;
    return 0;
}