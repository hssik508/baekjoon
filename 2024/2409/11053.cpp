#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n), dp(n, 1); // dp: i번째 항이 가질 수 있는 부분 수열의 최대 길이 저장, 각 항이 가질 수 있는 최소 길이인 1로 초기화
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    for (int i=1; i<n; i++)
    {
        for (int j=0; j<i; j++)
        {
            if (v[i]>v[j])
                dp[i]=max(dp[i], dp[j]+1); // 기존에 갱신한 값과 새로 갱신하게 될 값을 비교
        }
    }
    int MAX=0;
    for (int i=0; i<n; i++)
    {
        if (dp[i]>MAX)
            MAX=dp[i];
    }
    cout<<MAX;
    return 0;
}