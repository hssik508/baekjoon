#include <iostream>

using namespace std;

int mom[1000001]; // 부모 저장용

int getparent(int x) // 경로 압축
{
    if (mom[x] == x)
        return x;
    return mom[x] = getparent(mom[x]);
}

void unions(int a, int b) // 연결
{
    int aMom=getparent(a);
    int bMom=getparent(b);
    if (aMom<bMom)
        mom[bMom]=aMom;
    else
        mom[aMom]=bMom;
}

bool find(int a, int b) // 부모 같은지 확인
{
    return getparent(a)==getparent(b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    for (int i=0; i<=1000000; i++)
        mom[i]=i;
    int n, m;
    cin>>n>>m;
    int uf, a, b;
    for (int i=0; i<m; i++)
    {
        cin>>uf>>a>>b;
        if (uf==0)
            unions(a,b);
        else
        {
            if (find(a,b))
                cout<<"YES"<<'\n';
            else
                cout<<"NO"<<'\n';
        }
    }
    return 0;
}