#include <iostream>

using namespace std;

int value[101] = {0};
int dp[10001];

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    for (int i = 0; i <= 10000; i++) {
        dp[i] = 12345678; // 일단 모두 불가능한 경우로 초기화
    }
    dp[0] = 0; // 0원 만드는건 동전 0개 고정

    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (value[j] <= i)
                dp[i] = min(dp[i], dp[i - value[j]] + 1);
        }
    }

    cout << (dp[k] == 12345678 ? -1 : dp[k]); // 연산자 우선순위를 고려하여 삼항 연산자를 괄호로 먼저 묶어줘야함
    return 0;
}