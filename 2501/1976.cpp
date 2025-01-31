#include <iostream>

using namespace std;

int mom[201]={0};

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
    for (int i=1; i<=200; i++)
        mom[i]=i;
    int n, m, num;
    cin>>n>>m;
    for (int i=1; i<=n; i++) 
    {
        for (int j=1; j<=n; j++) 
        {
            cin>>num;
            if (num==1)
                Union(i, j);
        }
    }
    int root[1000]={0};
    string s="YES";
    for (int i=0; i<m; i++) 
    {
        cin>>root[i];
        if (i==0) 
            continue;
        if (!Find(root[i], root[i-1]))
            s="NO";
    }
    cout<<s;
    return 0;
}