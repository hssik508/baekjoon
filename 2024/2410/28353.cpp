#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int i = 0, j = n - 1, cnt = 0;
    while (i < j)
    {
        if (v[i] + v[j] <= k)
        {
            cnt++;
            i++;
            j--;
        }
        else
            j--;
    }
    cout << cnt;
    return 0;
}