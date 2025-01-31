#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<int> enter(n+1); // 인디그리
    vector<vector<pair<int,int>>> v(n+1);
    int x, y, k;
    for (int i=0; i<m; i++)
    {
        cin>>x>>y>>k; // x부품을 만들려면 y부품이 k개 필요함
        v[y].push_back({x,k}); // y가 k개 있어야 x를 만들 수 있다는 의미
        enter[x]++;
    }
    vector<int> basic(n+1); // 기본템이 몇번인지 알려주는 용도
    queue<int> q;
    for (int i=1; i<=n; i++)
    {
        if (enter[i]==0) // 기본템 체크
        {
            basic[i]=1;
            q.push(i);
        }
    }
    vector<vector<int>> dp(n+1, vector<int>(n+1)); // 행과 열은 모두 아이템 번호이며, a열의 아이템을 만들려면 무슨 아이템이 몇개 필요한지 행을 통해 알 수 있음
    while (!q.empty())
    {
        int node=q.front();
        q.pop();
        for (size_t i=0; i<v[node].size(); i++)
        {
            int next=v[node][i].first; 
            int nodeCnt=v[node][i].second; // next를 만들려면 필요한 node의 개수
            for (int j=1; j<=n; j++)
            {
                dp[j][next]+=dp[j][node]*nodeCnt;
            }
            dp[node][next]+=nodeCnt;
            enter[next]--;
            if (enter[next]==0) // 위상 정렬 처리
                q.push(next);
        }
    }
    for (int i=1; i<=n; i++)
    {
        if (basic[i]==1)
            cout<<i<<' '<<dp[i][n]<<'\n';
    }
    return 0;
}