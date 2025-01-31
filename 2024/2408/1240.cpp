// DFS로 푸는게 더 빠를 가능성 높음
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, n1, n2, dist;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v(n+1);
    for (int i=0; i<n-1; i++)
    {
        cin>>n1>>n2>>dist;
        v[n1].push_back({n2, dist});
        v[n2].push_back({n1, dist});        
    }
    for (int i=0; i<m; i++)
    {
        cin>>n1>>n2;
        queue<pair<int,int>> q;
        vector<bool> visit(n);
        q.push({n1,0});
        visit[n1]=true;
        while (1)
        {
            int node=q.front().first;
            int dist=q.front().second;
            if (node==n2)
            {
                cout<<dist<<'\n';
                break;
            }
            for (size_t i=0; i<v[node].size(); i++)
            {
                if (visit[v[node][i].first]==true) continue;
                q.push({v[node][i].first, v[node][i].second+dist});
                visit[v[node][i].first]=true;
            }
            q.pop();
        }
    }
    return 0;
}