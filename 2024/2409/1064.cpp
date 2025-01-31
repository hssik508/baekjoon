#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int xa, xb, xc, ya, yb, yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;
    double AC = sqrt(pow(xc - xa, 2) + pow(yc - ya, 2));
    double BC = sqrt(pow(xc - xb, 2) + pow(yc - yb, 2));
    double AB = sqrt(pow(xb - xa, 2) + pow(yb - ya, 2));

    if ((xb - xa) * (yc - yb) == (xc - xb) * (yb - ya)) // 세 점이 일직선상에 있는경우
    {
        cout << -1.0;
        return 0;
    }
    // 1. AD와 BC가 평행, AB와 CD가 평행
    // 2. AD와 BC가 평행, AC와 BD가 평행
    // 3. AB와 CD가 평행, AC와 BD가 평행
    // *** 참고로 점 D의 좌표는 굳이 구할 필요 없음 ***
    double d1 = 2 * (AB + BC);
    double d2 = 2 * (BC + AC);
    double d3 = 2 * (AB + AC);
    double ans = max({d1, d2, d3}) - min({d1, d2, d3});

    cout.precision(15);
    cout << ans;
    return 0;
}