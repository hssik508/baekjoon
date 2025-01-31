#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, c;
    cin >> n >> c;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int left = 1, right = v[n - 1] - v[0], max_mindist = 1; 
    // left와 right값은 가능한 두 공유기 사이의 거리를 의미하므로 각 지점의 좌표와는 무관함(left!=v[0])
    while (left <= right)
    {
        int mid = (left + right) / 2; // 두 공유기 사이 최소 거리
        int last = v[0], cnt = 1;
        for (int i = 1; i < n; i++)
        {
            if (v[i]-last >= mid)
            {
                last = v[i];
                cnt++;
            }
        }
        if (cnt >= c)
        {
            left = mid + 1;
            if (mid > max_mindist)
                max_mindist = mid;
        }    
        else
            right = mid - 1;
    }
    cout << max_mindist;
    return 0;
}