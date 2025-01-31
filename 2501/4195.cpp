#include <iostream>
#include <unordered_map>

using namespace std;

int mom[200001]={0};
int friendCnt[200001]={0}; // 특정 노드가 갖는 친구 관계수 
int cnt=0; // 존재하는 사람 수

void reset()
{
    for (int i=1; i<=200000; i++)
    {
        mom[i]=i;
        friendCnt[i]=1;
    }
    cnt=0;
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
    {
        mom[B]=A;
        friendCnt[A]+=friendCnt[B];
    }
    else if (A>B) // 주어진 두 친구의 부모가 같은 경우 결합시키면 안됨
    {
        mom[A]=B;
        friendCnt[B]+=friendCnt[A];
    }
}

bool Find(int a, int b)
{
    return getparent(a)==getparent(b);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        reset();
        int n;
        cin>>n;
        string s1, s2;
        unordered_map<string, int> m;
        for (int i=0; i<n; i++)
        {
            cin>>s1>>s2;
            if (m[s1]==0)
            {
                cnt++;
                m[s1]=cnt;
            }
            if (m[s2]==0)
            {
                cnt++;
                m[s2]=cnt;
            }
            int a=m[s1];
            int b=m[s2];
            Union(a,b);
            if (Find(a,b))
                cout<<friendCnt[getparent(a)]<<'\n';
            else
                cout<<0<<'\n';
        }
    }
    return 0;
}