#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, s, m;
    cin>>n>>s>>m;
    int v[51]={0};
    vector<vector<int>> dp(n+1); // 구간별로 가능한 모든 볼륨을 다 구해야 하므로 링크드 리스트 형태의 벡터로 관리
    for (int i=1; i<=n; i++)
        cin>>v[i];
    dp[0].push_back(s);

    for (int i=1; i<=n; i++)
    {
        unordered_map<int, bool> u; // 중복 제거
        if (dp[i-1].size()==0)
        {
            cout<<-1;
            return 0;
        }
        for (size_t j=0; j<dp[i-1].size(); j++)
        {
            int plus=dp[i-1][j]+v[i];
            int minus=dp[i-1][j]-v[i];
            if (plus<=m)
            {
                if (u[plus]==false)
                {
                    u[plus]=true;
                    dp[i].push_back(plus);
                }
            }
            if (minus>=0)
            {
                if (u[minus]==false)
                {
                    u[minus]=true;
                    dp[i].push_back(minus);
                }
            }
        }
    }

    // for (int i=0; i<=n; i++)
    // {
    //     for (size_t j=0; j<dp[i].size(); j++)
    //     {
    //         cout<<dp[i][j]<<' ';
    //     }
    //     cout<<'\n';
    // }

    int max=-1; // 맨 마지막 dp[n] 벡터에 들어있는 아무것도 존재하지 않는 경우가 있을수도 있으므로 -1로 초기화
    for (size_t i=0; i<dp[n].size(); i++)
    {
        if (dp[n][i]>max)
            max=dp[n][i];
    }
    cout<<max;
    return 0;
}