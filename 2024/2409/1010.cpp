#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    // 단순하게 nCr로 풀면 long long을 써도 29팩토리얼을 구할 수 없음.
    // 파스칼의 삼각형의 성질인 nCr = n-1Cr-1 + n-1Cr 이용
    int arr[30][30] = {0};
    arr[0][0] = 1;
    for (int i = 1; i < 30; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0)
            {
                arr[i][j] = 1;
                continue;
            }
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        cout << arr[m][n] << '\n';
    }
    return 0;
}