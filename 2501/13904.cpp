#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<pair<int,int>> v(n);
    for (int i=0; i<n; i++)
    {
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(), v.end()); // 과제 마감 일수가 적게 남은 것부터 앞에 오도록 정렬
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i=0; i<n; i++)
    {
        pq.push(v[i].second);
        if ((int)pq.size()>v[i].first) // 현재 과제가 마감 기한을 넘긴 경우
            pq.pop();
    }
    int scoreSum=0;
    while (!pq.empty())
    {
        scoreSum+=pq.top();
        pq.pop();
    }
    cout<<scoreSum;
    return 0;
}