#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> v(n+1);
    vector<int> enter(n+1);
    int a, b;
    for (int i=0; i<m; i++)
    {
        cin>>a>>b;
        v[a].push_back(b);
        enter[b]++;
    }
    queue<int> q;
    for (int i=1; i<=n; i++)
    {
        if (enter[i]==0)
            q.push(i);
    }
    while (!q.empty())
    {
        int node=q.front();
        q.pop();
        cout<<node<<' ';
        for (size_t i=0; i<v[node].size(); i++)
        {
            int next=v[node][i];
            if (--enter[next]==0)
                q.push(next);
        }
    }
    return 0;
}