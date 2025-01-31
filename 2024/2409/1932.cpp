#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> v(n + 1, vector<int>(n + 1));
    vector<vector<int>> hap(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cin >> v[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            hap[i][j] = max(hap[i - 1][j], hap[i - 1][j - 1]) + v[i][j];
        }
    }
    int MAX = 0;
    for (int i = 1; i <= n; i++)
    {
        if (hap[n][i] > MAX)
            MAX = hap[n][i];
    }
    cout << MAX;
    return 0;
}