#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n+1);
    vector<int> dp(n+1);
    for (int i=1; i<=n; i++)
    {
        cin>>v[i];
    }
    dp[1]=v[1];
    dp[2]=v[1]+v[2];
    for (int i=3; i<=n; i++)
    {
        dp[i]=max({dp[i-3]+v[i-1]+v[i], dp[i-2]+v[i], dp[i-1]}); // i번째 포도주를 안마시는 경우가 최선의 경우일 수도 있음
    }
    cout<<dp[n];
    return 0;
}

/* 조금 비효율적인 풀이
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n+1);
    vector<int> dp(n+1);
    for (int i=1; i<=n; i++)
    {
        cin>>v[i];
    }
    dp[1]=v[1];
    dp[2]=v[1]+v[2];
    dp[3]=max(v[1], v[2])+v[3];
    int MAX=max(dp[2], dp[3]); // dp[2]가 dp[3]보다 클 수 있음
    for (int i=4; i<=n; i++)
    {
        dp[i]=max({dp[i-4]+v[i-1]+v[i], dp[i-3]+v[i-1]+v[i], dp[i-2]+v[i]}); // 포도주를 2개 연속으로 안 마시는 경우까지 고려해야 함
        if (dp[i]>MAX)
            MAX=dp[i];
    }
    if (n<3)
        cout<<dp[n];
    else
        cout<<MAX;
    return 0;
}
*/

/* 주요 반례
6
1 1 0 0 1 1
답: 4

3
55 44 0
답: 99
*/