#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    vector<int> ab, cd;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ab.push_back(a[i] + b[j]);
            cd.push_back(c[i] + d[j]);
        }
    }
    sort(ab.begin(), ab.end());
    sort(cd.begin(), cd.end());
    long long cnt = 0; // 최대 4000^4
    int left = 0, right = cd.size() - 1;
    while ((size_t)left < cd.size() && right >= 0)
    {
        if (ab[left] + cd[right] < 0)
            left++;
        else if (ab[left] + cd[right] > 0)
            right--;
        else
        // ab cd 배열의 값이 이렇게 나온 경우도 고려해야함
        // 2 -2
        // 2 -2
        // 2 -2
        // 2 -2
        // 혹은
        // 0 0
        {
            int tmpLeftIdx = left, tmpRightIdx = right;
            long long tmpLeftCnt = 0, tmpRightCnt = 0;
            while ((size_t)tmpLeftIdx < ab.size() && ab[tmpLeftIdx] == ab[left])
            {
                tmpLeftCnt++;
                tmpLeftIdx++;
            }
            while (tmpRightIdx >= 0 && cd[tmpRightIdx] == cd[right])
            {
                tmpRightCnt++;
                tmpRightIdx--;
            }
            cnt += tmpLeftCnt * tmpRightCnt;
            left = tmpLeftIdx;
            right = tmpRightIdx;
        }
    }
    cout << cnt;
    return 0;
}