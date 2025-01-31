#include <iostream>
#include <queue>

using namespace std;

int n,m,v;
int arr[1001][1001]={0};
bool vis[1001]={false};
queue<int> q;

void dfs(int st)
{
    cout<<st<<' ';
    vis[st]=true;
    for (int i=1; i<=n; i++)
    {
        if (vis[i] || arr[st][i]==0)
            continue;
        dfs(i);
    }
    return;
}

void bfs(int st)
{
    bool visit[1001]={false};
    q.push(st);
    visit[st]=true;
    while (!q.empty())
    {
        int node=q.front();
        cout<<node<<' ';
        q.pop();
        for (int i=1; i<=n; i++)
        {
            if (visit[i] || arr[node][i]==0)
                continue;
            q.push(i);
            visit[i]=true;
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m>>v;
    int n1, n2;
    for (int i=0; i<m; i++)
    {
        cin>>n1>>n2;
        arr[n1][n2]=1;
        arr[n2][n1]=1;
    }
    dfs(v);
    cout<<'\n';
    bfs(v);
    return 0;
}