#include <iostream>
#include <vector>

using namespace std;

struct s
{
    int st;
    int end;
    int dist;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, d;
    cin>>n>>d;
    vector<s> v(n); // 지름길 정보 저장
    vector<int> dp(d+1); 
    for (int i=0; i<n; i++)
    {
        cin>>v[i].st>>v[i].end>>v[i].dist;
    }
    // 초기식: dp[0]=0; 이지만 벡터 생성하면서 dp벡터의 모든 값이 0으로 자동초기화 됐으므로 pass
    // 고속도로 길이가 1일 때부터 차례로 best case를 구한 후 dp 배열에 저장, 길이가 d일때까지 반복(배낭문제 처럼 접근)
    for (int i=1; i<=d; i++)
    {
        dp[i]=dp[i-1]+1; // 우선 (이전 위치까지 오는 최소 거리 + 1) 해준게 최소 거리라고 가정
        for (int j=0; j<n; j++)
        {
            if (v[j].end==i) 
                dp[i]=min(dp[v[j].st]+v[j].dist, dp[i]); // (지름길 시작지점까지 오는 최소 거리 + 지름길 길이)와 현재 dp[i]값을 비교하여 최솟값 갱신
        }
    }
    cout<<dp[d];
    return 0;
}