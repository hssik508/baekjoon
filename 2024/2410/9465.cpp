#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t, n;
    cin >> t;
    while (t--)
    {
        cin >> n;
        vector<vector<int>> v(2, vector<int>(n + 1));
        vector<vector<int>> dp(2, vector<int>(n + 1));
        for (int i = 0; i <= 1; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> v[i][j];
            }
        }

        dp[0][1] = v[0][1];
        dp[1][1] = v[1][1];
        for (int i = 0; i <= 1; i++)
        {
            for (int j = 2; j <= n; j++)
            {
                dp[0][j] = max(dp[1][j - 1], dp[1][j - 2]) + v[0][j];
                dp[1][j] = max(dp[0][j - 1], dp[0][j - 2]) + v[1][j];
            }
        }
        cout << max(dp[0][n], dp[1][n]) << '\n';
    }
    return 0;
}

/*
<기본 원리>
스티커 영역을
1 2 3
4 5 6
이라 할 때 6번 스티커를 떼는 경우는 4->2->6의 경우와 1->6의 경우 총 2가지가 있음.
따라서 두 경우를 비교하여 최대값을 dp배열 6번 자리에 넣어줘야 함.
이때 4->2->6을 통해 오는 경우는 2번 dp배열엔 2번 스티커를 떼는 best 경우가 저장되어있으므로 
결과적으로 6번 스티커를 떼는 경우를 고려할 땐 1번 dp배열과 6번 dp배열만 비교하면 된다.
dp배열은 스티커가 1열까지만 있는 경우, 2열까지만 있는 경우, 3열까지만 있는 경우... n열까지 있는 경우 
이런 식으로 부분 문제를 하나씩 해결하면서 채워나가면 된다. -> 계단 오르기 문제, RGB 거리 문제 발상 생각하기
*/