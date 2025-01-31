#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> v(n+1);
    vector<int> before(n+1);
    vector<int> ans(n+1,1);
    int n1, n2;
    for (int i=0; i<m; i++)
    {
        cin>>n1>>n2;
        v[n1].push_back(n2);
        before[n2]++;
    }
    queue<int> q;
    for (int i=0; i<n; i++)
    {
        if (before[i]==0)
            q.push(i);
    }
    while (!q.empty())
    {
        int node=q.front();
        q.pop();
        for (size_t i=0; i<v[node].size(); i++)
        {
            int next=v[node][i];
            before[next]--;
            if (before[next]==0)
                q.push(next);
            if (ans[node]+1>ans[next])
                ans[next]=ans[node]+1;
        }
    }
    for (int i=1; i<=n; i++)
        cout<<ans[i]<<' ';
    return 0;
}