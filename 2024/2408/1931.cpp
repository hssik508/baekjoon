#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
    if (a.second == b.second) // 회의 끝나는 시간이 같은 경우 회의 길이가 짧은 녀석이 최대한 나중에 오도록 정렬
        return a.first < b.first;
    return a.second < b.second;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].first >> v[i].second;
    }

    sort(v.begin(), v.end(), compare); // 회의 끝나는 시간 기준 정렬해야 최적해 보장

    int end = v[0].second, cnt = 1;
    for (int i = 1; i < n; i++)
    {
        if (v[i].first >= end)
        {
            cnt++;
            end = v[i].second;
        }
    }
    cout << cnt;
    return 0;
}