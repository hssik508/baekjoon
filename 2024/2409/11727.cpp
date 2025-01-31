#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int dp[1001]={0};
    dp[1]=1;
    dp[2]=3;
    // * 핵심: 경우의 수를 셀 때 중복되면 안됨
    // 맨 왼쪽에 오는 도형이 1x2, 2x1 2개가 위아래로 누워있는 경우, 2x2 총 3가지 경우 가능
    // 각 도형을 왼쪽에 두었을 때 남은 오른쪽 칸의 가로 길이를 m이라 하면 각 도형별로 나올 수 있는 경우 dp[m]
    // 3가지 도형별로 나온 경우의 수 다 더해주기
    for (int i=3; i<=n; i++)
    {
        dp[i]=(dp[i-1]+dp[i-2]*2)%10007;
    }
    cout<<dp[n];
    return 0;
}