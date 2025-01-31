#include <iostream>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        long long price[1000001];
        for (int i=1; i<=n; i++)
        {
            cin>>price[i];
        }
        long long max=price[n], sum=0;
        // 매커니즘: 가장 비싼날 싹 다 파는게 이득, 가장 비싼날이 되어 모두 팔았으면 그 다음날부터 마지막날까지 구간 중 가장 비싼날 또 싹 다 팔기
        // 그날 볼 수 있는 최대 이득: 구간 내에서 가장 비싼 날 가격 - 현재 가격 
        for (int i=n-1; i>=1; i--) // 뒤에서부터 탐색해야 시간복잡도 줄일 수 있음
        {
            if (price[i]<max)
                sum+=max-price[i];
            else
                max=price[i];
        }
        cout<<sum<<'\n';
    }
    return 0;
}