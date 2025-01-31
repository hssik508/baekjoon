#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> dp(1000001); // 1을 만드는데 걸리는 횟수, 최소 횟수를 만들어주는 이전 숫자
    dp[1] = {0, 0};
    for (int i = 2; i <= 1000000; i++)
    {
         // 기본적으로 1을 빼는 경우로 초기화
        dp[i].first = dp[i - 1].first + 1;
        dp[i].second = i - 1;
        // 2로 나누는 경우와 비교
        if (i % 2 == 0 && dp[i / 2].first + 1 < dp[i].first)
        {
            dp[i].first = dp[i / 2].first + 1;
            dp[i].second = i / 2;
        }
        // 3으로 나누는 경우와 비교
        if (i % 3 == 0 && dp[i / 3].first + 1 < dp[i].first)
        {
            dp[i].first = dp[i / 3].first + 1;
            dp[i].second = i / 3;
        }
    }
    cout << dp[n].first << '\n';
    int target = n;
    while (1)
    {
        cout << target << ' ';
        if (target == 1)
            break;
        target = dp[target].second;
    }
    return 0;
}