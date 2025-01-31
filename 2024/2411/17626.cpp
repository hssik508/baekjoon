#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[50001] = {0};
    int dp[50001] = {0};
    for (int i = 1; i <= 223; i++) // 223^2=49729
    {
        arr[i * i] = i;
        dp[i * i] = 1;
    }
    for (int i = 1; i <= 50000; i++)
    {
        if (arr[i] == 0)
            arr[i] = arr[i - 1];
    }
    for (int i = 1; i <= 50000; i++)
    {
        int min = 4;
        for (int j = 1; j <= arr[i]; j++)
        {
            if (dp[j * j] + dp[i - j * j] < min)
                min = dp[j * j] + dp[i - j * j];
        }
        dp[i] = min;
    }
    cout << dp[n];
    return 0;
}