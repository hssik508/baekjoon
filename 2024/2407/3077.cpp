#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    string s;
    unordered_map<string, int> ans;
    vector<int> v(n);

    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        ans[s] = i;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v[i] = ans[s];
    }

    int cnt = 0, ssang = (n * (n - 1)) / 2;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (v[i] < v[j])
                cnt++;
        }
    }

    cout << cnt << '/' << ssang << '\n';
    return 0;
}

/* 비효율적인 코드
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    string s;
    unordered_map<string, int> ans;
    vector<string> v(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        ans[s] = i;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        v[i] = s;
    }
    int cnt = 0, ssang = (n * (n - 1)) / 2;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ans[v[j]] - ans[v[i]] > 0)
                cnt++;
        }
    }
    cout << cnt << '/' << ssang;
    return 0;
}
*/