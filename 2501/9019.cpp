#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int a, b;
        cin>>a>>b;
        bool visit[10001]={false}; // 중복 방문 처리해줘야 시간 초과 및 메모리 초과 안됨
        queue<pair<int,string>> q; // string: 명령어 나열
        q.push({a,""});
        visit[a]=true;
        while (q.front().first!=b)
        {
            int num=q.front().first;
            string st=q.front().second;
            q.pop();
            int d=(2*num)%10000;
            int s=(num==0)?9999:num-1;
            int l=(num%1000)*10+num/1000; // 덱으로 구현하면 시간초과 되므로 몫과 나머지 연산으로 l과 r을 구해야함
            int r=(num%10)*1000+num/10;
            if (visit[d]==false)
            {
                q.push({d, st+'D'});
                visit[d]=true;
            }
            if (visit[s]==false)
            {
                q.push({s, st+'S'});
                visit[s]=true;
            }
            if (visit[l]==false)
            {
                q.push({l, st+'L'});
                visit[l]=true;
            }
            if (visit[r]==false)
            {
                q.push({r, st+'R'});
                visit[r]=true;
            }
        }
        cout<<q.front().second<<'\n';
    }
    return 0;
}