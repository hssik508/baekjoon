#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    int max = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        if (v[i] > max)
            max = v[i];
        sum += v[i];
    }
    int left = max, right = sum, min = right;
    while (left <= right)
    {
        int mid = (left + right) / 2; // mid는 블루레이 크기를 의미함
        int sum = 0, cnt = 1;
        for (int i = 0; i < n; i++)
        {
            if (sum + v[i] > mid)
            {
                cnt++;
                sum = 0;
            }
            sum += v[i];
        }
        if (cnt <= m)
        {
            if (mid < min)
                min = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    cout << min;
    return 0;
}