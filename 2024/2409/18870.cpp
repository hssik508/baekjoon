#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.second < b.second;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<pair<int, int>, int>> v(n); // <<좌표,압축적용결과>,입력받은순서>
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first.first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    int cnt = 0;
    v[0].first.second = 0;
    for (int i = 1; i < n; i++)
    {
        if (v[i].first.first == v[i - 1].first.first)
            v[i].first.second = cnt;
        else
            v[i].first.second = ++cnt;
    }
    sort(v.begin(), v.end(), compare);
    for (int i = 0; i < n; i++)
    {
        cout << v[i].first.second << ' ';
    }
    return 0;
}