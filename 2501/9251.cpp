#include <iostream>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string a, b;
    cin>>a>>b;
    // 편집 거리 문제처럼 접근하기
    int dp[1001][1001]={0};
    for (size_t i=1; i<=a.size(); i++)
    {
        for (size_t j=1; j<=b.size(); j++)
        {
            if (a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }
    cout<<dp[a.size()][b.size()];
    return 0;
}
