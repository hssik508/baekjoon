#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n), dp(n, 1);
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    int MAX=0;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<i; j++)
        {
            if (v[i]<v[j])
                dp[i]=max(dp[i], dp[j]+1);
        }
        if (dp[i]>MAX)
            MAX=dp[i];
    }
    cout<<MAX;
    return 0;
}