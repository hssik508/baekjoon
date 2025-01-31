#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    long long n, m;
    cin >> n >> m;
    vector<long long> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    long long left = 0, right = v[n - 1], maxheight = 0;
    while (left <= right)
    {
        long long mid = (left + right) / 2, sum = 0;
        for (int i = 0; i < n; i++)
        {
            if (v[i] - mid <= 0)
                continue;
            sum += v[i] - mid;
        }
        // 높이의 합이 목표높이보다 낮으면 왼쪽 탐색(더 낮은 높이에서 잘라야 함)
        // 같거나 크면 오른쪽 탐색(더 높은 높이에서 잘라도 됨)
        if (sum < m)
        {
            right = mid - 1;
        }
        else
        {
            if (mid > maxheight)
                maxheight = mid;
            left = mid + 1;
        }
    }
    cout << maxheight;
    return 0;
}