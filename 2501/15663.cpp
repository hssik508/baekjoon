#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> suyeol;
vector<int> visit(8);
vector<int> print(8);
int n, m;

void dfs(int level)
{
    if (level==m)
    {
        for (int i=0; i<m; i++)
        {
            cout<<print[i]<<' ';
        }
        cout<<'\n';
        return;
    }
    else
    {
        map<int, bool> ma; // 같은 레벨 내에서는 숫자가 중복되지 않게 처리해줘야 함
        for (int i=0; i<n; i++)
        {
            if (visit[i]==false && ma[suyeol[i]]==false)
            {
                visit[i]=true;
                print[level]=suyeol[i];
                ma[suyeol[i]]=true;
                dfs(level+1);
                visit[i]=false;
            }
        }
    }
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    int num;
    for (int i=0; i<n; i++)
    {
        cin>>num;
        suyeol.push_back(num);
    }
    sort(suyeol.begin(), suyeol.end());
    dfs(0);
    return 0;
}