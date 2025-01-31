#include <iostream>
#include <vector>

using namespace std;

int mom[51];

int getparent(int x)
{
    if (mom[x]==x)
        return x;
    return mom[x]=getparent(mom[x]);
}

void Union(int a, int b)
{
    int A=getparent(a), B=getparent(b);
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
    for (int i=0; i<=50; i++)
        mom[i]=i;
    int n, m;
    cin>>n>>m;
    int trueNum;
    cin>>trueNum;
    if (trueNum==0)
    {
        cout<<m;
        return 0;
    }
    vector<int> truth(trueNum);
    for (int i=0; i<trueNum; i++)
        cin>>truth[i];

    int n1, n2;
    vector<vector<int>> party(m);
    for (int i=0; i<m; i++)
    {
        cin>>n1;
        for (int j=0; j<n1; j++)
        {
            cin>>n2;
            party[i].push_back(n2);
            if (j>=1) // 파티에 온 인원수가 2명 이상인 경우 유니온 진행 
                Union(party[i][j], party[i][j-1]);
        }
    }
    vector<int> truthroot(trueNum); // 파티가 끝난 후 기존에 진실을 알던 사람들의 루트번호를 갱신하여 저장
    for (int i=0; i<trueNum; i++)
    {
        truthroot[i]=mom[truth[i]];
    }

    int cnt=0;
    for (int i=0; i<m; i++)
    {
        int gura=1;
        for (size_t j=0; j<party[i].size(); j++)
        {
            int node=party[i][j];
            for (int k=0; k<trueNum; k++)
            {
                if (Find(truthroot[k], node)) // 진실 아는 사람의 루트번호와 비교
                {
                    gura=0;
                    break;
                }
            }
            if (!gura)
                break;
        }
        if (gura)
            cnt++;
    }
    cout<<cnt;
    return 0;
}

// 반례

// input
// 5 4
// 1 5
// 2 1 2
// 2 2 3
// 2 3 4
// 2 4 5

// ans
// 0

// wrong output
// 2
