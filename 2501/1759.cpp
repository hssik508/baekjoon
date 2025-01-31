#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 암호 조건: 자음 2개 이상, 모음 1개 이상, 문자열이 사전순으로 증가
int l, c;
vector<char> pw;
vector<char> ch(15);
int jaeum=0; 
int moeum=0;

bool is_moeum(char ch)
{
    if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u')
        return true;
    return false;
}

void dfs(int st, int level)
{
    if (level==l)
    {
        if (moeum>=1 && jaeum>=2)
        {
            for (int i=0; i<level; i++)
                cout<<ch[i];
            cout<<'\n';
        }
    }
    else
    {
        for (int i=st; i<c; i++)
        {
            ch[level]=pw[i];
            if (is_moeum(pw[i]))
                moeum++;
            else
                jaeum++;
            dfs(i+1, level+1);
            if (is_moeum(pw[i]))
                moeum--;
            else
                jaeum--;
        }
    }
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);
    cin>>l>>c;
    pw.resize(c);
    for (int i=0; i<c; i++) 
    {
        cin>>pw[i];
    }
    sort(pw.begin(), pw.end());
    dfs(0,0);
    return 0;
}