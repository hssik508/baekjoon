#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    long long arr[101];
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    long long dp[101][21] = {0};
    dp[1][arr[1]]++;
    for (int i=2; i<n; i++)
    {
        for (int j=0; j<=20; j++)
        {
            if (dp[i-1][j]!=0)
            {
                if (j+arr[i]<=20)
                    dp[i][j+arr[i]]+=dp[i-1][j];
                if (j-arr[i]>=0)
                    dp[i][j-arr[i]]+=dp[i-1][j];
            }
        }
    }
    cout<<dp[n-1][arr[n]];
    return 0;
}