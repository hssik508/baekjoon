#include <iostream>

using namespace std;

// 행: 소요 일 수(n), n<=200
// 열: 챕터 번호(1~m), m<=20

int main()
{
    int n, m;
    cin>>n>>m;
    int weight[21]={0};
    int value[21]={0};
    for (int i=1; i<=m; i++)
    {
        cin>>weight[i]>>value[i];
    }
    int dp[21][201]={0};
    for (int i=1; i<=m; i++) // i: 행, j: 열
    {
        for (int j=1; j<=n; j++)
        {
            if (weight[i]>j)
                dp[i][j]=dp[i-1][j];
            else
                dp[i][j]=max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i]); // j: 현재 임시배낭 용량,  weight[i]: 현재 넣고자 하는 물건 무게
        }
    }
    cout<<dp[m][n];
    return 0;
}