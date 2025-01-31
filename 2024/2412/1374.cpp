#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<pair<int,int>> v(n);
    int num;
    for (int i=0; i<n; i++)
    {
        cin>>num>>v[i].first>>v[i].second;
    }
    sort(v.begin(), v.end());
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i=0; i<n; i++)
    {
        pq.push(v[i].second);
        if (v[i].first>=pq.top())
            pq.pop();
    } 
    cout<<pq.size();
    return 0;
}