#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string a, b;
    cin>>a>>b;
    int n = (int)a.size(), m = (int)b.size();
    int dp[1001][1001]={0}; // 행: 문자열 a, 열: 문자열 b, dp[i][j]가 의미하는것: 문자열 a의 0~i번째 문자를 문자열 b의 0~j번째 문자로 만드는 최소 횟수
    for (int i=1; i<=n; i++)
    {
        dp[i][0]=i;
    }
    for (int j=1; j<=m; j++)
    {
        dp[0][j]=j;
    }
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            if (a[i-1]==b[j-1]) // 특정 위치의 비교 문자열이 같은경우
                dp[i][j]=dp[i-1][j-1];
            else
                dp[i][j]=min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]})+1; // min 3개이상 쓰려면 algorithm 헤더파일 선언해야함
        }
    }
    cout<<dp[n][m];
    return 0;
}