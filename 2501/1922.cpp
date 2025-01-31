#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mom[1001];

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

bool cmp(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b)
{
    return a.second<b.second;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int i=0; i<=1000; i++)
        mom[i]=i;
    int n, m;
    cin>>n>>m;
    vector<pair<pair<int,int>,int>> v(m);
    for (int i=0; i<m; i++)
        cin>>v[i].first.first>>v[i].first.second>>v[i].second;

    sort(v.begin(), v.end(), cmp);
    int cnt=0, weight=0, iter=0, n1, n2;
    while (cnt<n-1)
    {
        n1=v[iter].first.first;
        n2=v[iter].first.second;
        if (Find(n1, n2))
        {
            iter++;
            continue;
        }
        Union(n1, n2);
        weight+=v[iter].second;
        cnt++;
        iter++;
    }
    cout<<weight;
    return 0;
}