#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<pair<int, int>> v(n);
        for (int j = 0; j < n; j++)
        {
            cin >> v[j].first;
            v[j].second = j + 1;
        }
        sort(v.begin(), v.end(), compare);
        if (v[0].first == v[1].first)
            cout << "no winner" << '\n';
        else
        {
            int sum = 0;
            for (size_t k = 1; k < v.size(); k++)
            {
                sum += v[k].first;
            }
            if (v[0].first > sum)
                cout << "majority winner " << v[0].second << '\n';
            else
                cout << "minority winner " << v[0].second << '\n';
        }
    }
    return 0;
}