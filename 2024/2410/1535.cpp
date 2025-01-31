#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int blood[21]={0}, happy[21]={0};
    for (int i=1; i<=n; i++)
    {
        cin>>blood[i];
    }
    for (int i=1; i<=n; i++)
    {
        cin>>happy[i];
    }
    // 체력 99까지 허용 가능
    int dp[21][100]={0};
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=99; j++)
        {
            if (blood[i]>j)
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j], dp[i-1][j-blood[i]]+happy[i]);
        }
    }
    cout<<dp[n][99];
    return 0;
}