#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t, n, mon;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<int> v(n+1);
        for (int i = 1; i <= n; i++)
        {
            cin >> v[n];
        }
        cin >> mon;
        vector<vector<int>> dp(n + 1, vector<int>(mon + 1));
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=mon; j++)
            {
                

                dp[i][j]=dp[i-1][j]+dp[i][j-v[i]];
            }
        }
    }
}