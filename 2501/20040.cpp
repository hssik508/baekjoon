#include <iostream>

using namespace std;

int mom[500000];

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

bool Find(int a, int b)
{
    return getparent(a)==getparent(b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int i=0; i<500000; i++)
        mom[i]=i;
    int n, m, n1, n2;
    cin>>n>>m;
    int cycle=1, signal=0, ans=0;
    for (int i=0; i<m; i++)
    {
        cin>>n1>>n2;
        if (signal==0 && Find(n1, n2))
        {
            signal=1;
            ans=cycle;
        }
        Union(n1, n2);
        cycle++;
    }
    cout<<ans;
    return 0;
}