#include <iostream>
#include <queue>

using namespace std;

int mx[]={1,1,1,0,0,-1,-1,-1};
int my[]={0,1,-1,1,-1,-1,1,0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    while (1)
    {
        int w, h;
        cin>>w>>h;
        if (w==0 && h==0)
            break;
        int v[52][52]={0};
        for (int i=1; i<=h; i++) {
            for (int j=1; j<=w; j++) {
                cin>>v[i][j];
            }
        }

        queue<pair<int,int>> q;
        bool visit[52][52]={false};
        int cnt=0;
        for (int i=1; i<=h; i++) {
            for (int j=1; j<=w; j++) {
                if (v[i][j]==1 && visit[i][j]==false)
                {
                    q.push({i,j});
                    visit[i][j]=true;
                    while (!q.empty())
                    {
                        int x=q.front().first;
                        int y=q.front().second;
                        q.pop();
                        for (int k=0; k<8; k++)
                        {
                            int nx=x+mx[k];
                            int ny=y+my[k];
                            if (nx<1 || ny<1 || nx>h || ny>w || v[nx][ny]==0 || visit[nx][ny]==true)
                                continue;
                            visit[nx][ny]=true;
                            q.push({nx,ny});
                        }
                    }
                    cnt++;
                }
            }
        }
        cout<<cnt<<'\n';
    }
    return 0;
}