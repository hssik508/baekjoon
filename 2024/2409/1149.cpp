#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Price
{
    int red;
    int green;
    int blue;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<Price> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].red >> v[i].green >> v[i].blue;
    }
    vector<vector<int>> hap(3, vector<int>(n));
    // i번째 집을 특정 색으로 칠했을때의 누적 최소 비용 저장
    hap[0][0] = v[0].red;
    hap[1][0] = v[0].green;
    hap[2][0] = v[0].blue;
    // i번째 집을 무슨색으로 칠하느냐에 따라 case 분류 (dp적 사고)
    for (int i = 1; i < n; i++)
    {
        hap[0][i] = v[i].red + min(hap[1][i - 1], hap[2][i - 1]);
        hap[1][i] = v[i].green + min(hap[0][i - 1], hap[2][i - 1]);
        hap[2][i] = v[i].blue + min(hap[0][i - 1], hap[1][i - 1]);
    }

    int res = min({hap[0][n - 1], hap[1][n - 1], hap[2][n - 1]});
    cout << res;
    return 0;
}