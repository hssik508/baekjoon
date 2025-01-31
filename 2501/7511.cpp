#include <iostream>

using namespace std;

int mom[1000000];

void reset(int n)
{
    for (int i=0; i<n; i++)
        mom[i]=i;
}

int getparent(int x)
{
    if (mom[x]==x)
        return x;
    return mom[x]=getparent(mom[x]);
}

void Union(int a, int b)
{
    int A=getparent(a);
    int B=getparent(b);
    if (A<B)
        mom[B]=A;
    else
        mom[A]=B;
}

int Find(int a, int b)
{
    return getparent(a)==getparent(b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t, num=1;
    cin>>t;
    while (t--)
    {
        int n, k, a, b, m, u, v;
        cin>>n>>k;
        reset(n);
        for (int i=0; i<k; i++)
        {
            cin>>a>>b;
            Union(a,b);
        }
        cin>>m;
        cout<<"Scenario "<<num++<<":\n";
        for (int i=0; i<m; i++)
        {
            cin>>u>>v;
            cout<<Find(u,v)<<'\n';
        }
        cout<<'\n';
    }
    return 0;
}