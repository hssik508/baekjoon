#include <iostream>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        long long dp[10][65]={0};
        for (int i=0; i<=64; i++)
            dp[0][i]=1;
        for (int i=1; i<=9; i++)
        {
            for (int j=1; j<=n; j++)
            {
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        long long sum=0;
        for (int i=0; i<=9; i++)
        {
            sum+=dp[i][n];
        }
        cout<<sum<<'\n';
    }
    return 0;
}