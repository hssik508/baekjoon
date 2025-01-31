#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int dp[31]={0};
    dp[2]=3;
    for (int i=4; i<=30; i++)
    {
        if (i%2==1)
            continue;
        dp[i]+=dp[i-2]*3; // 일단 이전 dp값과 dp[2]값을 곱함
        for (int j=4; j<i; j=j+2)
        {
            dp[i]+=dp[j-2]*2; // 나머지 값들이 중복 안되게 하려면 '특별한 모양'이 생기는 경우인 2씩 곱해서 더해줘야함
        }
        dp[i]+=2; // '특별한 모양' 이 생기는 경우는 각각의 3*N 타일 마다 2개씩 존재함
    }
    cout<<dp[n];
    return 0;
}

// 참고: https://yabmoons.tistory.com/536