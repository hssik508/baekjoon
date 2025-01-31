#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mom[10001];

bool compare(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b)
{
    return a.second<b.second;
}

int getparent(int x)
{
    if (mom[x]==x)
        return x;
    return mom[x]=getparent(mom[x]);
}

void unions(int a, int b)
{
    int aMom=getparent(a);
    int bMom=getparent(b);
    if (aMom<bMom)
        mom[bMom]=aMom;
    else
        mom[aMom]=bMom;
}

bool find(int a, int b)
{
    return getparent(a)==getparent(b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int i=0; i<=10000; i++)
        mom[i]=i;
    int v, e, a, b, c;
    cin>>v>>e;
    vector<pair<pair<int,int>,int>> tree(e);
    for (int i = 0; i < e; i++) 
    {
        cin>>a>>b>>c;
        tree[i]={{a,b},c};
    }
    sort(tree.begin(), tree.end(), compare);
    int n1, n2, weight, pos=0, weightSum=0, vertexCnt=0;
    // 최소 스패닝 트리에서 간선의 개수는 (정점 개수 - 1)개
    while (vertexCnt<v-1) 
    {
        n1=tree[pos].first.first;
        n2=tree[pos].first.second;
        weight=tree[pos].second;
        if (find(n1, n2)) // 사이클 생기면 스킵
        {
            pos++;
            continue;
        }
        weightSum+=weight;
        unions(n1, n2);
        vertexCnt++;
        pos++;
    }
    cout<<weightSum;
    return 0;
}