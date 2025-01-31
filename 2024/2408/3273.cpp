#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, x, cnt = 0;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    cin >> x;
    sort(v.begin(), v.end());
    int left = 0, right = n - 1;
    while (left < right)
    {
        if (v[left] + v[right] > x)
            right--;
        else if (v[left] + v[right] < x)
            left++;
        else
        {
            cnt++;
            left++;
            right--;
        }
    }
    cout << cnt;
    return 0;
}

/*
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, x, cnt = 0;
    cin >> n;
    vector<int> v(n);
    unordered_map<int, int> num;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        num[v[i]]++;
    }
    cin >> x;
    for (int i = 0; i < n; i++)
    {
        if (x - v[i] == v[i])
            cnt += num[v[i]] - 1;
        else
            cnt += num[x - v[i]];
        num[v[i]] = 0;
    }
    cout << cnt;
    return 0;
}
*/