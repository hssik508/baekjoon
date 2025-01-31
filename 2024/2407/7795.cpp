#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int left = 0, right = m - 1;
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (b[mid] >= a[i])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            cnt += left;
        }
        cout << cnt << '\n';
    }
    return 0;
}

/* 다른 풀이
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (a[i] > b[j])
                    cnt++;
                else
                    break;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}

*/