#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

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
    sort(v.begin(), v.end()); // 강의 시작 시간 기준 정렬
    priority_queue<int, vector<int>, greater<>> pq; // 강의 끝나는 시간이 빠른 애부터 오름차순 정렬
    pq.push(v[0].second);
    for (int i = 1; i < n; i++)
    {
        if (v[i].first >= pq.top())
            pq.pop();
        pq.push(v[i].second);
    }
    cout << pq.size();
    return 0;
}