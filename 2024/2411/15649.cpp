#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> arr(9);
vector<bool> visit(9);

void dfs(int level)
{
    if (level==m)
    {
        for (int i=0; i<m; i++)
            cout<<arr[i]<<' ';
        cout<<'\n';
        return;
    }
    for (int i=1; i<=n; i++)
    {
        if (!visit[i])
        {
            visit[i]=true;
            arr[level]=i;
            dfs(level+1);
            visit[i]=false;
        }
    }
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    dfs(0);
    return 0;
}