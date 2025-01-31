#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin>>n>>k; // k -> 배낭 최대 용량
    vector<int> weight(n+1), value(n+1);
    for (int i=1; i<=n; i++)
    {
        cin>>weight[i]>>value[i];
    }
    vector<vector<int>> dp(n+1, vector<int> (k+1));
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=k; j++)
        {
            if (weight[i]>j)
                dp[i][j]=dp[i-1][j];
            else
            {
                dp[i][j]=max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i]); 
                // 현재 물건을 넣지 않는 경우의 가치 -> 기존에 저장되어있던 최대 가치 가져오면 됨
                // 현재 물건을 넣는 경우 -> (임시 배낭 용량 - 현재 물건 무게)를 기준으로 잡았을 때의 최대 가치 + 현재 물건 가치
            }
        }
    }
    cout<<dp[n][k];
    return 0;
}