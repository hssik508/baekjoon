#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int dp[10][1001]={0};
    for (int i=0; i<=9; i++)
    {
        dp[i][1]=1;
    }

    for (int i=0; i<=9; i++)
    {
        for (int j=2; j<=n; j++)
        {
            int sum=0;
            for (int k=0; k<=i; k++)
            {
                sum+=dp[k][j-1]%10007;
            }
            dp[i][j]=sum%10007;
        }
    }
    int sum=0;
    for (int i=0; i<=9; i++)
    {
        sum+=dp[i][n];
    }
    cout<<sum%10007;
    return 0;
}