#include <iostream>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    string s;
    cin>>s;
    int cnt=0, IOIcnt=0; // cnt: 최종 정답, IOIcnt: IOI패턴이 몇번 반복되는지 저장하는 임시 변수
    for (int i=2; i<m; i++)
    {
        if (s[i]=='I' && s[i-1]=='O' && s[i-2]=='I')
            IOIcnt++;
        if (IOIcnt>0 && s[i]==s[i-1])
        {
            if (IOIcnt>=n)
                cnt+=(IOIcnt-n)+1;
            IOIcnt=0;
        }
    }
    if (IOIcnt>0) // 문자열 맨 끝이 IOI 혹은 IO로 끝나는 경우 예외처리
    {
        if (IOIcnt>=n)
            cnt+=(IOIcnt-n)+1;
    }
    cout<<cnt;
    return 0;
}