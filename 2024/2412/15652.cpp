#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v(9);

void nm(int st, int level)
{
    if (level==m)
    {
        for (int i=0; i<m; i++)
            cout<<v[i]<<' ';
        cout<<'\n';
        return;
    }

    for (int i=st; i<=n; i++)
    {
        v[level]=i;
        nm(i, level+1);
    }
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    nm(1,0);
    return 0;
}