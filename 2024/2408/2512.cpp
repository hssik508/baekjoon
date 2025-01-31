#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    long long n, money, sum = 0;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        sum += v[i];
    }
    cin >> money;
    sort(v.begin(), v.end());
    if (sum <= money)
    {
        cout << v[n - 1];
        return 0;
    }
    long long left = 1, right = v[n - 1], max = 0; // left: 가능한 최소 상한액, right: 가능한 최대 상한액
    while (left <= right)
    {
        long long mid = (left + right) / 2, sum = 0; // mid: 상한액
        for (int i = 0; i < n; i++)
        {
            if (v[i] <= mid)
                sum += v[i];
            else
                sum += mid;
        }
        if (sum <= money)
        {
            if (mid > max)
                max = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    cout << max;
    return 0;
}